#pragma once

#include <cobalt/macros.hpp>
#include <cobalt/containers/smartpointers.hpp>

#include <cobalt/graphics/graphicscontext.hpp>

#include <unordered_map>

namespace cobalt
{
	class Texture;
	class Mesh;
	
	struct TextureCreateInfo;
	
	enum class EResourceType : uint32_t
	{
		TEXTURE_2D,
		MESH
	};

	template<EResourceType Type>
	struct ResourceHandle
	{
		static constexpr EResourceType type = Type;
		std::uint32_t identifier;

		bool operator==(const ResourceHandle& other) const
		{
			return (type == other.type) && (identifier == other.identifier);
		}
	};

	class Resource
	{
		public:
			virtual ~Resource() = default;

			std::string name;
	};

	class ResourceManager
	{
		public:
			explicit ResourceManager(UniquePtr<GraphicsContext>& graphics);
			~ResourceManager();

			COBALT_NO_DISCARD static ResourceManager* get() noexcept;
		
			COBALT_NO_COPY_MOVE(ResourceManager)

			ResourceHandle<EResourceType::TEXTURE_2D> loadTexture(const std::string_view path, const std::string_view name, const TextureCreateInfo& loadInfo);
			ResourceHandle<EResourceType::TEXTURE_2D> getTextureHandle(const std::string_view name);
			Texture* getTexture(const ResourceHandle<EResourceType::TEXTURE_2D> handle);

			ResourceHandle<EResourceType::MESH> loadMesh(const std::string_view path, const std::string_view name);
			ResourceHandle<EResourceType::MESH> getMeshHandle(const std::string_view name);
			Mesh* getMesh(const ResourceHandle<EResourceType::MESH> handle);

		private:
			template<typename Application>
			friend class Engine;
		
			UniquePtr<GraphicsContext>& _graphics;
			std::unordered_map<EResourceType, std::unordered_map<uint32_t, UniquePtr<Resource>>> _resources;
			std::unordered_map<EResourceType, int32_t> _resourceIdentifiers;

			static ResourceManager* _instance;
	};
}
