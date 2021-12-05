#include <cobalt/graphics/mesh.hpp>

namespace cobalt
{
	Mesh::Mesh(const UniquePtr<GraphicsContext>& context, const std::vector<MeshVertex>& vertices,
		const std::vector<uint32_t>& indices)
	{
		_vertexBuffer = MakeUnique<VertexBuffer>(context, vertices.data(), sizeof(MeshVertex) * vertices.size());
		_indexBuffer = MakeUnique<IndexBuffer>(context, indices.data(), sizeof(uint32_t) * indices.size());
	}
}
