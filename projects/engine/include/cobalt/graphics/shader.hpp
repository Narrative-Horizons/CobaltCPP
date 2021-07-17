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
			ShaderResource();
			~ShaderResource();

		protected:
			friend class ShaderResourceHelper;

			struct ShaderResourceImpl;
			ShaderResourceImpl* _impl;
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
			~Shader();

			COBALT_NO_COPY_MOVE(Shader)

			void setData(ShaderType shaderType, ShaderResourceType resourceType, std::string_view name, ShaderResource& data) const;
			void setDataArray(ShaderType shaderType, ShaderResourceType resourceType, std::string_view name, ShaderResource& data) const;
			void setData(ShaderType shaderType, const ShaderResourceType resourceType, const std::string_view name, const Framebuffer& framebuffer, uint32_t index) const;

		private:
			friend class ShaderHelper;
		
			struct ShaderImpl;
			ShaderImpl* _impl;
	};
}
