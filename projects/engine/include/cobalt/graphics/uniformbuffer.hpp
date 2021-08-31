#pragma once

#include <cobalt/containers/smartpointers.hpp>

#include <cobalt/graphics/graphicsenums.hpp>
#include <cobalt/graphics/shader.hpp>

namespace cobalt
{
	class UniformBuffer : public ShaderResource
	{
		public:
			// TODO: Add bind type
			UniformBuffer(const UniquePtr<GraphicsContext>& context, ShaderResourceType type, size_t size, const std::string& name);
			~UniformBuffer() = default;

			void setData(const void* data, ResourceStateTransitionMode transitionMode);

		private:
			Diligent::RefCntAutoPtr<Diligent::IBuffer> _buffer;
			const UniquePtr<GraphicsContext>& _context;
			size_t _size;
	};
}