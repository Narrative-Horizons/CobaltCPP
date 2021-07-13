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
		Diligent::RefCntAutoPtr<Diligent::IShader> vShader;
		Diligent::RefCntAutoPtr<Diligent::IShader> pShader;
		Diligent::RefCntAutoPtr<Diligent::IShader> cShader;
		Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> srb;
		std::vector<Diligent::ShaderResourceVariableDesc> vars;
		std::vector<Diligent::ImmutableSamplerDesc> samplers;
	};

	struct ShaderResource::ShaderResourceImpl
	{
		Diligent::RefCntAutoPtr<Diligent::IDeviceObject> objectData;
	};

	class ShaderHelper
	{
		public:
			explicit ShaderHelper(const Shader& shader);

			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IPipelineState> getPipeline() const;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShader> getVertexShader() const;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShader> getPixelShader() const;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShader> getComputeShader() const;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> getResourceBinding() const;

		private:
			const Shader& _shader;
	};

	class ShaderResourceHelper
	{
		public:
			explicit ShaderResourceHelper(const ShaderResource& resource);

			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IDeviceObject> getResourceObject() const;

		private:
			const ShaderResource& _resource;
	};
}
