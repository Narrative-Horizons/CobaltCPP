#pragma once

#include <vector>

#include <cobalt/graphics/graphicsenums.hpp>
#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/graphics/sampler.hpp>

namespace cobalt
{
	class ShaderResource
	{
		public:
			ShaderResource() = default;
			~ShaderResource() = default;

			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IDeviceObject> getResourceObject() const;
			//COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IDeviceObject*> getResourceObjects() const;
			COBALT_NO_DISCARD uint32_t getResourceObjectsCount() const;

		protected:
			Diligent::RefCntAutoPtr<Diligent::IDeviceObject> _objectData;
			//Diligent::RefCntAutoPtr<Diligent::IDeviceObject*> arrayData;

			uint32_t _numElements = 1;
	};
	
	struct ShaderResourceDesc
	{
		ShaderType shaderStages = ShaderType::UNKNOWN;
		std::string name;
		ShaderResourceType type = ShaderResourceType::STATIC;
		ShaderVariableFlags flags = ShaderVariableFlags::NONE;

		ShaderResource* resource = nullptr;

		ShaderResourceDesc() = default;

		ShaderResourceDesc(const ShaderType shaderStages,
		                   const std::string& name,
		                   const ShaderResourceType type,
		                   const ShaderVariableFlags flags,
						   ShaderResource* resource = nullptr) noexcept :
				shaderStages{ shaderStages },
				name{ name },
				type{ type },
				flags{ flags },
				resource{resource}
		{}
	};
	
	struct ShaderCreateInfo
	{
		std::string name;
		std::string vertexSource;
		std::string pixelSource;
		std::string geometrySource;
		std::string hullSource;
		std::string domainSource;
		std::string computeSource;
		
		std::vector<TextureFormat> renderTargetFormats;
		TextureFormat depthTargetFormat = TextureFormat::UNKNOWN;
		PrimitiveTopology primitiveTopology;
		CullMode cullMode;
		FillMode fillMode;
		bool depthEnable;
		bool depthWrite;

		std::vector<ShaderResourceDesc> shaderResources;
		std::vector<ImmutableSampler> immutableSamplers;
	};
	
	class Shader
	{
		public:
			Shader(const GraphicsContext& context, ShaderCreateInfo& createInfo);
			~Shader() = default;

			COBALT_NO_COPY_MOVE(Shader)

			void setData(ShaderType shaderType, ShaderResourceType resourceType, std::string_view name, ShaderResource& data);
			void setDataArray(ShaderType shaderType, ShaderResourceType resourceType, std::string_view name, ShaderResource& data);
			void setData(ShaderType shaderType, const ShaderResourceType resourceType, const std::string_view name, Framebuffer& framebuffer, uint32_t index);

			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IPipelineState> getPipeline() const;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShader> getVertexShader() const;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShader> getPixelShader() const;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShader> getComputeShader() const;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> getResourceBinding() const;

		private:
			Diligent::PIPELINE_TYPE _type;
			Diligent::RefCntAutoPtr<Diligent::IPipelineState> _pipeline;
			Diligent::RefCntAutoPtr<Diligent::IShader> _vShader;
			Diligent::RefCntAutoPtr<Diligent::IShader> _pShader;
			Diligent::RefCntAutoPtr<Diligent::IShader> _cShader;
			Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> _srb;
			std::vector<Diligent::ShaderResourceVariableDesc> _vars;
			std::vector<Diligent::ImmutableSamplerDesc> _samplers;
	};
}
