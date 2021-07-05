#include <cobalt/graphics/shader.hpp>

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>

namespace cobalt
{
	struct Shader::ShaderImpl
	{
		Diligent::PIPELINE_TYPE type;
		Diligent::RefCntAutoPtr<Diligent::IPipelineState> pipeline;
		Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> bindings;
	};

	Shader::Shader()
	{
		_impl = new ShaderImpl;
	}

	Shader::~Shader()
	{
		delete _impl;
		_impl = nullptr;
	}

	std::unique_ptr<Shader> Shader::createRasterizerShader(std::string_view name,
		std::string_view vertexSource,
		std::string_view pixelSource,
		std::string_view geometrySource,
		std::string_view hullSource,
		std::string_view domainSource)
	{
		using namespace Diligent;
		GraphicsPipelineStateCreateInfo psoInfo;
		PipelineStateDesc& psoDesc = psoInfo.PSODesc;
		psoDesc.PipelineType = PIPELINE_TYPE_GRAPHICS;
		
		std::string pipelineName(name);
		psoDesc.Name = pipelineName.c_str();

		constexpr uint32_t vertexLayoutCount = 5;
		LayoutElement vertexLayouts[vertexLayoutCount] = {
			LayoutElement{0, 0, 3, VT_FLOAT32, False}, // Position
			LayoutElement{1, 0, 2, VT_FLOAT32, False}, // UV0
			LayoutElement{2, 0, 3, VT_FLOAT32, False}, // Normal
			LayoutElement{3, 0, 3, VT_FLOAT32, False}, // Tangent
			LayoutElement{4, 0, 3, VT_FLOAT32, False}, // Bitangent
		};

		psoInfo.GraphicsPipeline.InputLayout.NumElements = vertexLayoutCount;
		psoInfo.GraphicsPipeline.InputLayout.LayoutElements = vertexLayouts;
		psoDesc.ResourceLayout.DefaultVariableType = SHADER_RESOURCE_VARIABLE_TYPE_STATIC;

		auto shader = std::make_unique<Shader>();
		shader->_impl->type = psoDesc.PipelineType;

		return shader;
	}

	std::unique_ptr<Shader> Shader::createComputeShader(std::string_view computeSource)
	{
		return std::make_unique<Shader>();
	}
}