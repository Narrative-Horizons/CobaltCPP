#include "shaderhelper.hpp"

namespace cobalt
{
	ShaderHelper::ShaderHelper(const Shader& shader) : _shader(shader) { }

	Diligent::RefCntAutoPtr<Diligent::IPipelineState> ShaderHelper::getPipeline() const
	{
		return _shader._impl->pipeline;
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

	Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> ShaderHelper::getResourceBinding() const
	{
		return _shader._impl->srb;
	}

	ShaderResourceHelper::ShaderResourceHelper(const ShaderResource& resource) : _resource(resource) { }

	Diligent::RefCntAutoPtr<Diligent::IDeviceObject> ShaderResourceHelper::getResourceObject() const
	{
		return _resource._impl->objectData;
	}

	/*Diligent::RefCntAutoPtr<Diligent::IDeviceObject*> ShaderResourceHelper::getResourceObjects() const
	{
		return _resource._impl->arrayData;
	}*/

	uint32_t ShaderResourceHelper::getResourceObjectsCount() const
	{
		return _resource._impl->numElements;
	}
}
