#include <cobalt/graphics/shader.hpp>

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>

#include <cobalt/graphics/graphicscontexthelper.hpp>

namespace cobalt
{
	struct Shader::ShaderImpl
	{
		Diligent::PIPELINE_TYPE type;
		Diligent::RefCntAutoPtr<Diligent::IPipelineState> pipeline;
		Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> bindings;
		Diligent::RefCntAutoPtr<Diligent::IShader> vShader;
		Diligent::RefCntAutoPtr<Diligent::IShader> pShader;

		~ShaderImpl()
		{
			//vShader.Release();
			//pShader.Release();
			//bindings.Release();
			//pipeline.Release();
		}
	};

	Shader::Shader(const GraphicsContext& context, const ShaderCreateInfo& createInfo)
	{
		_impl = new ShaderImpl;

		using namespace Diligent;
		GraphicsPipelineStateCreateInfo graphicsPsoInfo;
		ComputePipelineStateCreateInfo computePsoInfo;
	
		auto contextHelper = new GraphicsContextHelper(context);

		std::string vertexShaderName = (createInfo.name + " VS");
		std::string pixelShaderName = (createInfo.name + " PS");
		std::string computeShaderName = (createInfo.name + " CS");
		std::string entryPoint = "main";

		constexpr uint32_t vertexLayoutCount = 6;
		LayoutElement vertexLayouts[vertexLayoutCount] = {
			LayoutElement{0, 0, 3, VT_FLOAT32, False}, // Position
			LayoutElement{1, 0, 2, VT_FLOAT32, False}, // UV0
			LayoutElement{2, 0, 3, VT_FLOAT32, False}, // Normal
			LayoutElement{3, 0, 3, VT_FLOAT32, False}, // Tangent
			LayoutElement{4, 0, 3, VT_FLOAT32, False}, // Bitangent
			LayoutElement{5, 1, 1, VT_UINT32, False, INPUT_ELEMENT_FREQUENCY_PER_INSTANCE} // InstanceID
		};

		if(!createInfo.computeSource.empty())
		{
			// This is a compute shader
			PipelineStateDesc& psoDesc = computePsoInfo.PSODesc;
			psoDesc.PipelineType = PIPELINE_TYPE_COMPUTE;

			psoDesc.Name = createInfo.name.c_str();

			Diligent::ShaderCreateInfo shaderCI;
			shaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
			shaderCI.UseCombinedTextureSamplers = true;

			// Vertex shader
			shaderCI.Desc.ShaderType = SHADER_TYPE_COMPUTE;
			shaderCI.EntryPoint = entryPoint.c_str();
			shaderCI.Desc.Name = computeShaderName.c_str();
			shaderCI.Source = createInfo.vertexSource.c_str();

			RefCntAutoPtr<IShader> cShader;
			contextHelper->getRenderDevice()->CreateShader(shaderCI, &cShader);

			computePsoInfo.pCS = cShader;
		}
		else
		{
			// This is not a compute shader
			PipelineStateDesc& psoDesc = graphicsPsoInfo.PSODesc;
			psoDesc.PipelineType = PIPELINE_TYPE_GRAPHICS;

			psoDesc.Name = createInfo.name.c_str();

			graphicsPsoInfo.GraphicsPipeline.InputLayout.NumElements = vertexLayoutCount;
			graphicsPsoInfo.GraphicsPipeline.InputLayout.LayoutElements = vertexLayouts;
			psoDesc.ResourceLayout.DefaultVariableType = SHADER_RESOURCE_VARIABLE_TYPE_STATIC;

			_impl->type = psoDesc.PipelineType;
			
			Diligent::ShaderCreateInfo shaderCI;
			shaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
			shaderCI.UseCombinedTextureSamplers = true;

			// Vertex shader
			shaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
			shaderCI.EntryPoint = entryPoint.c_str();
			shaderCI.Desc.Name = vertexShaderName.c_str();
			shaderCI.Source = createInfo.vertexSource.c_str();
			
			contextHelper->getRenderDevice()->CreateShader(shaderCI, &_impl->vShader);

			graphicsPsoInfo.pVS = _impl->vShader;

			if(!createInfo.pixelSource.empty())
			{
				// Pixel shader
				shaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
				shaderCI.EntryPoint = entryPoint.c_str();
				shaderCI.Desc.Name = pixelShaderName.c_str();
				shaderCI.Source = createInfo.pixelSource.c_str();

				contextHelper->getRenderDevice()->CreateShader(shaderCI, &_impl->pShader);
				graphicsPsoInfo.pPS = _impl->pShader;
			}
		}

		if(!createInfo.shaderResources.empty())
		{
			PipelineStateDesc& psoDesc = graphicsPsoInfo.PSODesc;
			std::vector<ShaderResourceVariableDesc> vars;
			for(const auto& resource : createInfo.shaderResources)
			{
				ShaderResourceVariableDesc var{ static_cast<SHADER_TYPE>(resource.shaderStages), resource.name.c_str(),
					static_cast<SHADER_RESOURCE_VARIABLE_TYPE>(resource.type), static_cast<SHADER_VARIABLE_FLAGS>(resource.flags) };

				vars.push_back(var);
			}

			psoDesc.ResourceLayout.Variables = &vars[0];
			psoDesc.ResourceLayout.NumVariables = static_cast<uint32_t>(vars.size());
		}

		if(!createInfo.immutableSamplers.empty())
		{
			std::vector<ImmutableSamplerDesc> samplers;
			for(const auto& [shaderStages, name, sampler] : createInfo.immutableSamplers)
			{
				SamplerDesc samplerDesc{ static_cast<FILTER_TYPE>(sampler.minFilter), static_cast<FILTER_TYPE>(sampler.magfilter), static_cast<FILTER_TYPE>(sampler.mipFilter),
				static_cast<TEXTURE_ADDRESS_MODE>(sampler.addressU), static_cast<TEXTURE_ADDRESS_MODE>(sampler.addressV), static_cast<TEXTURE_ADDRESS_MODE>(sampler.addressW),
				sampler.mipLODBias, sampler.maxAnisotropy, static_cast<COMPARISON_FUNCTION>(sampler.comparisonFunc), sampler.minLOD, sampler.maxLOD };
				ImmutableSamplerDesc desc{ static_cast<SHADER_TYPE>(shaderStages), name.c_str(), samplerDesc };

				samplers.push_back(desc);
			}

			PipelineStateDesc& psoDesc = graphicsPsoInfo.PSODesc;
			psoDesc.ResourceLayout.ImmutableSamplers = &samplers[0];
			psoDesc.ResourceLayout.NumImmutableSamplers = static_cast<uint32_t>(samplers.size());
		}

		if(!createInfo.computeSource.empty())
		{
			contextHelper->getRenderDevice()->CreateComputePipelineState(computePsoInfo, &_impl->pipeline);
		}
		else
		{
			contextHelper->getRenderDevice()->CreateGraphicsPipelineState(graphicsPsoInfo, &_impl->pipeline);
		}
	}

	Shader::~Shader()
	{
		delete _impl;
		_impl = nullptr;
	}
}
