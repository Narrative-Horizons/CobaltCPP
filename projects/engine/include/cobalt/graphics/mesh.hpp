#pragma once

#include <cobalt/containers/smartpointers.hpp>

#include <cobalt/math/vec2.hpp>
#include <cobalt/math/vec3.hpp>
#include <cobalt/resources/resourcemanager.hpp>

#include <cobalt/graphics/vertexbuffer.hpp>
#include <cobalt/graphics/indexbuffer.hpp>

namespace cobalt
{
	struct MeshVertex
	{
		math::vec3 position;
		math::vec2 uv;
		math::vec3 normal;
		math::vec3 tangent;
		math::vec3 binormal;
	};
	
	class Mesh final : public Resource
	{
		public:
		
		private:
			friend class ResourceManager;

			Mesh(const UniquePtr<GraphicsContext>& context, const std::vector<MeshVertex>& vertices, const std::vector<uint32_t>& indices);

			UniquePtr<VertexBuffer> _vertexBuffer;
			UniquePtr<IndexBuffer> _indexBuffer;
	};
}
