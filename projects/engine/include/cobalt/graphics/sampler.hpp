#pragma once
#include <cobalt/graphics/graphicsenums.hpp>

namespace cobalt
{
	struct Sampler
	{
		FilterType minFilter = FilterType::LINEAR;
		FilterType magfilter = FilterType::LINEAR;
		FilterType mipFilter = FilterType::LINEAR;

		TextureAddressMode addressU = TextureAddressMode::CLAMP;
		TextureAddressMode addressV = TextureAddressMode::CLAMP;
		TextureAddressMode addressW = TextureAddressMode::CLAMP;

		float mipLODBias = 0.0f;
		uint32_t maxAnisotropy = 0;

		ComparisonFunction comparisonFunc = ComparisonFunction::NEVER;

		float borderColor[4] = {};

		float minLOD = 0.0f;
		float maxLOD = +3.402823466e+38F;
	};

	struct ImmutableSampler
	{
		ShaderType shaderStages = ShaderType::UNKNOWN;
		std::string name;
		Sampler sampler;
	};
}