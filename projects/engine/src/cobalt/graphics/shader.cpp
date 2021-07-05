#include <cobalt/graphics/shader.hpp>

namespace cobalt
{
	struct ShaderImpl
	{

	};

	Shader::Shader()
	{

	}

	Shader::~Shader()
	{

	}

	std::unique_ptr<Shader> Shader::createRasterizerShader(std::string_view vertexSource,
		std::string_view pixelSource = std::string_view(),
		std::string_view geometrySource = std::string_view(),
		std::string_view hullSource = std::string_view(),
		std::string_view domainSource = std::string_view())
	{
		return std::make_unique<Shader>();
	}

	std::unique_ptr<Shader> Shader::createComputeShader(std::string_view computeSource)
	{
		return std::make_unique<Shader>();
	}
}