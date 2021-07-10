#pragma once

#include <string_view>
#include <memory>
#include <vector>

#include <cobalt/graphics/graphicsenums.hpp>
#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/graphics/sampler.hpp>

namespace cobalt
{
	struct ShaderResourceDesc
	{
		ShaderType shaderStages = ShaderType::UNKNOWN;
		std::string name;
		ShaderResourceType type = ShaderResourceType::STATIC;
		ShaderVariableFlags flags = ShaderVariableFlags::NONE;

		ShaderResourceDesc() noexcept = default;

		ShaderResourceDesc(const ShaderType shaderStages,
		                   const std::string& name,
		                   const ShaderResourceType type,
		                   const ShaderVariableFlags flags = ShaderVariableFlags::NONE) noexcept :
				shaderStages{ shaderStages },
				name{ name },
				type{ type },
				flags{ flags }
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
	
	class Shader final
	{
		public:
			Shader(const GraphicsContext& context, ShaderCreateInfo& createInfo);
			~Shader();

		private:
			friend class ShaderHelper;
		
			struct ShaderImpl;
			ShaderImpl* _impl;
	};
}
