#pragma once
#include <vector>
#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/TextureView.h>

#include <cobalt/graphics/shader.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/PipelineState.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Shader.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/ShaderResourceBinding.h>

namespace cobalt
{
	struct Shader::ShaderImpl
	{
		Diligent::PIPELINE_TYPE type;
		Diligent::RefCntAutoPtr<Diligent::IPipelineState> pipeline;
		Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> bindings;
		Diligent::RefCntAutoPtr<Diligent::IShader> vShader;
		Diligent::RefCntAutoPtr<Diligent::IShader> pShader;
		Diligent::RefCntAutoPtr<Diligent::IShader> cShader;
	};

	class ShaderHelper
	{
	public:
		explicit ShaderHelper(const Shader& shader);

		COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IPipelineState> getPipeline() const;
		COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> getBindings() const;
		COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShader> getVertexShader() const;
		COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShader> getPixelShader() const;
		COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShader> getComputeShader() const;

	private:
		const Shader& _shader;
	};
}
