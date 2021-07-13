#pragma once

#include <cobalt/graphics/graphicsenums.hpp>
#include <cobalt/graphics/shader.hpp>

namespace cobalt
{
	class UniformBuffer : public ShaderResource
	{
		public:
			// TODO: Add bind type
			UniformBuffer(const GraphicsContext& context, ShaderResourceType type, size_t size, const std::string& name);
			~UniformBuffer();

			void setData(const void* data, ResourceStateTransitionMode transitionMode) const;

		private:
			struct UniformBufferImpl;
			UniformBufferImpl* _uimpl;
	};
}