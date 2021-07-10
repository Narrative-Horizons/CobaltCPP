#include "shaderhelper.hpp"

namespace cobalt
{
	ShaderHelper::ShaderHelper(const Shader& shader) : _shader(shader) { }

	Diligent::RefCntAutoPtr<Diligent::IPipelineState> ShaderHelper::getPipeline() const
	{
		return _shader._impl->pipeline;
	}

	Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> ShaderHelper::getBindings() const
	{
		return _shader._impl->bindings;
	}

	Diligent::RefCntAutoPtr<Diligent::IShader> ShaderHelper::getVertexShader() const
	{
		return _shader._impl->vShader;
	}

	Diligent::RefCntAutoPtr<Diligent::IShader> ShaderHelper::getPixelShader() const
	{
		return _shader._impl->pShader;
	}

	Diligent::RefCntAutoPtr<Diligent::IShader> ShaderHelper::getComputeShader() const
	{
		return _shader._impl->cShader;
	}
}
