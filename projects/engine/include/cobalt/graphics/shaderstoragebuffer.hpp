#pragma once

#include <cobalt/graphics/graphicsenums.hpp>
#include <cobalt/graphics/shader.hpp>

namespace cobalt
{
	class ShaderStorageBuffer : public ShaderResource
	{
		public:
			// TODO: Add bind type
			ShaderStorageBuffer(const GraphicsContext& context, ShaderResourceType type, size_t size, const std::string& name);
			~ShaderStorageBuffer();

			void setData(const void* data, ResourceStateTransitionMode transitionMode) const;

		private:
			struct ShaderStorageBufferImpl;
			ShaderStorageBufferImpl* _uimpl;
	};
}