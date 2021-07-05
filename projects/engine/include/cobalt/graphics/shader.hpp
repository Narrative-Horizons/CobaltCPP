#pragma once

#include <string_view>
#include <memory>

namespace cobalt
{
	class Shader
	{
		public:
			static std::unique_ptr<Shader> createRasterizerShader(std::string_view vertexSource,
				std::string_view pixelSource = std::string_view(),
				std::string_view geometrySource = std::string_view(),
				std::string_view hullSource = std::string_view(),
				std::string_view domainSource = std::string_view());

			static std::unique_ptr<Shader> createComputeShader(std::string_view computeSource);

			Shader();
			~Shader();

		private:
			struct ShaderImpl;
			ShaderImpl* _impl;
	};
}