#include <cobalt/graphics/shader.hpp>

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>

namespace cobalt
{
	Shader::Shader(const GraphicsContext& context, ShaderCreateInfo& createInfo)
	{
		using namespace Diligent;
		GraphicsPipelineStateCreateInfo graphicsPsoInfo;
		ComputePipelineStateCreateInfo computePsoInfo;
	
		std::string vertexShaderName = (createInfo.name + " VS");
		std::string pixelShaderName = (createInfo.name + " PS");
		std::string computeShaderName = (createInfo.name + " CS");
		std::string entryPoint = "main";

		constexpr uint32_t vertexLayoutCount = 2;
		LayoutElement vertexLayouts[vertexLayoutCount] = {
			LayoutElement{0, 0, 3, VT_FLOAT32, False}, // Position
			LayoutElement{1, 0, 2, VT_FLOAT32, False}, // UV0
			//LayoutElement{2, 0, 3, VT_FLOAT32, False}, // Normal
			//LayoutElement{3, 0, 3, VT_FLOAT32, False}, // Tangent
			//LayoutElement{4, 0, 3, VT_FLOAT32, False}, // Bitangent
			//LayoutElement{5, 1, 1, VT_UINT32, False, INPUT_ELEMENT_FREQUENCY_PER_INSTANCE} // InstanceID
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
			context.getRenderDevice()->CreateShader(shaderCI, &cShader);

			computePsoInfo.pCS = cShader;
		}
		else
		{
			// This is not a compute shader
			if(createInfo.renderTargetFormats.empty())
			{
				// Use swapchain
				createInfo.renderTargetFormats.push_back(static_cast<TextureFormat>(context.getSwapchain()->GetDesc().ColorBufferFormat));
				createInfo.depthTargetFormat = static_cast<TextureFormat>(context.getSwapchain()->GetDesc().DepthBufferFormat);
			}
			
			graphicsPsoInfo.GraphicsPipeline.NumRenderTargets = static_cast<uint8_t>(createInfo.renderTargetFormats.size())
			;
			uint32_t idx = 0;
			for(const auto& rtFormat : createInfo.renderTargetFormats)
			{
				graphicsPsoInfo.GraphicsPipeline.RTVFormats[idx++] = static_cast<TEXTURE_FORMAT>(rtFormat);
			}

			graphicsPsoInfo.GraphicsPipeline.DSVFormat = static_cast<TEXTURE_FORMAT>(createInfo.depthTargetFormat);
			
			PipelineStateDesc& psoDesc = graphicsPsoInfo.PSODesc;
			psoDesc.PipelineType = PIPELINE_TYPE_GRAPHICS;

			psoDesc.Name = createInfo.name.c_str();

			graphicsPsoInfo.GraphicsPipeline.PrimitiveTopology = static_cast<PRIMITIVE_TOPOLOGY>(createInfo.primitiveTopology);
			graphicsPsoInfo.GraphicsPipeline.RasterizerDesc.CullMode = static_cast<CULL_MODE>(createInfo.cullMode);
			graphicsPsoInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = createInfo.depthEnable;
			graphicsPsoInfo.GraphicsPipeline.DepthStencilDesc.DepthWriteEnable = createInfo.depthWrite;

			graphicsPsoInfo.GraphicsPipeline.InputLayout.NumElements = vertexLayoutCount;
			graphicsPsoInfo.GraphicsPipeline.InputLayout.LayoutElements = vertexLayouts;
			psoDesc.ResourceLayout.DefaultVariableType = SHADER_RESOURCE_VARIABLE_TYPE_STATIC;

			_type = psoDesc.PipelineType;
			
			Diligent::ShaderCreateInfo shaderCi;
			shaderCi.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
			shaderCi.UseCombinedTextureSamplers = true;

			// Vertex shader
			shaderCi.Desc.ShaderType = SHADER_TYPE_VERTEX;
			shaderCi.EntryPoint = entryPoint.c_str();
			shaderCi.Desc.Name = vertexShaderName.c_str();
			shaderCi.Source = createInfo.vertexSource.c_str();
			
			context.getRenderDevice()->CreateShader(shaderCi, &_vShader);

			graphicsPsoInfo.pVS = _vShader;

			if(!createInfo.pixelSource.empty())
			{
				// Pixel shader
				shaderCi.Desc.ShaderType = SHADER_TYPE_PIXEL;
				shaderCi.EntryPoint = entryPoint.c_str();
				shaderCi.Desc.Name = pixelShaderName.c_str();
				shaderCi.Source = createInfo.pixelSource.c_str();

				context.getRenderDevice()->CreateShader(shaderCi, &_pShader);
				graphicsPsoInfo.pPS = _pShader;
			}
		}

		if(!createInfo.shaderResources.empty())
		{
			PipelineStateDesc& psoDesc = graphicsPsoInfo.PSODesc;

			bool hasNonStaticResources = false;
			for(const auto& resource : createInfo.shaderResources)
			{
				if (resource.type == ShaderResourceType::STATIC)
					continue;

				hasNonStaticResources = true;
				
				ShaderResourceVariableDesc var{ static_cast<SHADER_TYPE>(resource.shaderStages), resource.name.c_str(),
					static_cast<SHADER_RESOURCE_VARIABLE_TYPE>(resource.type), static_cast<SHADER_VARIABLE_FLAGS>(resource.flags) };

				_vars.push_back(var);
			}

			if (hasNonStaticResources)
			{
				psoDesc.ResourceLayout.Variables = &_vars[0];
				psoDesc.ResourceLayout.NumVariables = static_cast<uint32_t>(_vars.size());
			}
		}

		if(!createInfo.immutableSamplers.empty())
		{
			
			for(const auto& [shaderStages, name, sampler] : createInfo.immutableSamplers)
			{
				SamplerDesc samplerDesc{ static_cast<FILTER_TYPE>(sampler.minFilter), static_cast<FILTER_TYPE>(sampler.magfilter), static_cast<FILTER_TYPE>(sampler.mipFilter),
				static_cast<TEXTURE_ADDRESS_MODE>(sampler.addressU), static_cast<TEXTURE_ADDRESS_MODE>(sampler.addressV), static_cast<TEXTURE_ADDRESS_MODE>(sampler.addressW),
				sampler.mipLODBias, sampler.maxAnisotropy, static_cast<COMPARISON_FUNCTION>(sampler.comparisonFunc), sampler.minLOD, sampler.maxLOD };
				ImmutableSamplerDesc desc{ static_cast<SHADER_TYPE>(shaderStages), name.c_str(), samplerDesc };

				_samplers.push_back(desc);
			}

			PipelineStateDesc& psoDesc = graphicsPsoInfo.PSODesc;
			psoDesc.ResourceLayout.ImmutableSamplers = &_samplers[0];
			psoDesc.ResourceLayout.NumImmutableSamplers = static_cast<uint32_t>(_samplers.size());
		}

		if(!createInfo.computeSource.empty())
		{
			context.getRenderDevice()->CreateComputePipelineState(computePsoInfo, &_pipeline);
		}
		else
		{
			context.getRenderDevice()->CreateGraphicsPipelineState(graphicsPsoInfo, &_pipeline);

			if (!createInfo.shaderResources.empty())
			{
				PipelineStateDesc& psoDesc = graphicsPsoInfo.PSODesc;
				std::vector<ShaderResourceVariableDesc> vars;
				for (const auto& resource : createInfo.shaderResources)
				{
					if (resource.type == ShaderResourceType::STATIC)
					{
						auto x = _pipeline->GetStaticVariableByName(static_cast<Diligent::SHADER_TYPE>(resource.shaderStages), resource.name.c_str());
						if (x == nullptr)
							continue; // TODO : print error
						
						x->Set(resource.resource->getResourceObject());
					}
				}
			}

			_pipeline->CreateShaderResourceBinding(&_srb, true);
		}
	}

	void Shader::setData(ShaderType shaderType, const ShaderResourceType resourceType, const std::string_view name, ShaderResource& data)
	{
		switch(resourceType)
		{
			case ShaderResourceType::MUTABLE:
			case ShaderResourceType::DYNAMIC:
			{
				auto x = _srb->GetVariableByName(static_cast<Diligent::SHADER_TYPE>(shaderType), name.data());
				x->Set(data.getResourceObject());
				break;
			}
		}
	}

	void Shader::setDataArray(ShaderType shaderType, ShaderResourceType resourceType, std::string_view name,
		ShaderResource& data)
	{
		switch (resourceType)
		{
			case ShaderResourceType::MUTABLE:
			case ShaderResourceType::DYNAMIC:
			{
				auto x = _srb->GetVariableByName(static_cast<Diligent::SHADER_TYPE>(shaderType), name.data());
				//x->SetArray(resourceHelper.getResourceObjects(), 0, resourceHelper.getResourceObjectsCount());
				break;
			}
		}
	}

	void Shader::setData(ShaderType shaderType, const ShaderResourceType resourceType, const std::string_view name, Framebuffer& framebuffer, const uint32_t index)
	{
		switch (resourceType)
		{
			case ShaderResourceType::MUTABLE:
			case ShaderResourceType::DYNAMIC:
			{
				auto x = _srb->GetVariableByName(static_cast<Diligent::SHADER_TYPE>(shaderType), name.data());
				x->Set(framebuffer.getRenderTarget(index, TextureTypeView::SHADER_RESOURCE));
				break;
			}
		}
	}

	Diligent::RefCntAutoPtr<Diligent::IPipelineState> Shader::getPipeline() const
	{
		return _pipeline;
	}

	Diligent::RefCntAutoPtr<Diligent::IShader> Shader::getVertexShader() const
	{
		return _vShader;
	}

	Diligent::RefCntAutoPtr<Diligent::IShader> Shader::getPixelShader() const
	{
		return _pShader;
	}

	Diligent::RefCntAutoPtr<Diligent::IShader> Shader::getComputeShader() const
	{
		return _cShader;
	}

	Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> Shader::getResourceBinding() const
	{
		return _srb;
	}

	Diligent::RefCntAutoPtr<Diligent::IDeviceObject> ShaderResource::getResourceObject() const
	{
		return _objectData;
	}

	/*Diligent::RefCntAutoPtr<Diligent::IDeviceObject*> ShaderResourceHelper::getResourceObjects() const
	{
		return _resource._impl->arrayData;
	}*/

	uint32_t ShaderResource::getResourceObjectsCount() const
	{
		return _numElements;
	}
}
