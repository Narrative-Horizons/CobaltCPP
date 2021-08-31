#pragma once

#include <cobalt/macros.hpp>
#include <cobalt/containers/smartpointers.hpp>

#include <cobalt/graphics/graphicscontext.hpp>

#include <unordered_map>

namespace cobalt
{
	class Texture;
	struct TextureCreateInfo;
	
	enum class EResourceType : uint32_t
	{
		TEXTURE_2D
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
			~ResourceManager();

			COBALT_NO_DISCARD static ResourceManager* get() noexcept;
		
			COBALT_NO_COPY_MOVE(ResourceManager)

			ResourceHandle<EResourceType::TEXTURE_2D> loadTexture(const std::string_view path, const std::string_view name, const TextureCreateInfo& loadInfo);
			ResourceHandle<EResourceType::TEXTURE_2D> getTextureHandle(const std::string_view name);
			Texture* getTexture(const ResourceHandle<EResourceType::TEXTURE_2D> handle);

			// TODO: Make private

		private:
			template<typename Application>
			friend class Engine;
		
			explicit ResourceManager(UniquePtr<GraphicsContext>& graphics);

		
			UniquePtr<GraphicsContext>& _graphics;
			std::unordered_map<EResourceType, std::unordered_map<uint32_t, UniquePtr<Resource>>> _resources;
			std::unordered_map<EResourceType, int32_t> _resourceIdentifiers;

			static ResourceManager* _instance;
	};
}