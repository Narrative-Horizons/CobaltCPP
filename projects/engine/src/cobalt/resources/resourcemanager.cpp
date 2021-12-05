#include <cobalt/resources/resourcemanager.hpp>
#include <cobalt/graphics/texture.hpp>
#include <cobalt/graphics/mesh.hpp>

#include <DiligentTools/AssetLoader/interface/GLTFLoader.hpp>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace cobalt
{
	ResourceManager* ResourceManager::_instance;
	
	ResourceManager::ResourceManager(UniquePtr<GraphicsContext>& graphics) : _graphics(graphics)
	{
		_resourceIdentifiers[EResourceType::TEXTURE_2D] = 0;
		_instance = this;
	}

	ResourceManager::~ResourceManager()
	{
		//_resources.clear();
	}

	ResourceManager* ResourceManager::get() noexcept
	{
		assert(_instance != nullptr);
		return _instance;
	}

	ResourceHandle<EResourceType::TEXTURE_2D> ResourceManager::loadTexture(const std::string_view path,
	                                                                       const std::string_view name, const TextureCreateInfo& loadInfo)
	{
		const int32_t identifier = ++_resourceIdentifiers[EResourceType::TEXTURE_2D];

		const UniquePtr<Image> image = MakeUnique<Image>(path.data());

		ResourceHandle<EResourceType::TEXTURE_2D> handle;
		handle.identifier = identifier;

		Texture* texture = new Texture(_graphics, image, loadInfo);
		_resources[EResourceType::TEXTURE_2D][identifier] = UniquePtr<Resource>(texture);
		_resources[EResourceType::TEXTURE_2D][identifier]->name = name;

		return handle;
	}

	ResourceHandle<EResourceType::TEXTURE_2D> ResourceManager::getTextureHandle(const std::string_view name)
	{
		for (auto& [indentifier, resource] : _resources[EResourceType::TEXTURE_2D])
		{
			if(resource->name == name)
			{
				ResourceHandle<EResourceType::TEXTURE_2D> handle;
				handle.identifier = indentifier;

				return handle;
			}
		}

		return ResourceHandle<EResourceType::TEXTURE_2D>();
	}

	Texture* ResourceManager::getTexture(const ResourceHandle<EResourceType::TEXTURE_2D> handle)
	{
		const auto res = _resources[EResourceType::TEXTURE_2D].at(handle.identifier).get();
		return static_cast<Texture*>(res);
	}

	ResourceHandle<EResourceType::MESH> ResourceManager::loadMesh(const std::string_view path,
		const std::string_view name)
	{
		const int32_t identifier = ++_resourceIdentifiers[EResourceType::MESH];

		ResourceHandle<EResourceType::MESH> handle;
		handle.identifier = identifier;

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.data(), aiProcessPreset_TargetRealtime_MaxQuality);
		
		std::vector<MeshVertex> verts;
		std::vector<uint32_t> triangles;
		
		Mesh* mesh = new Mesh(_graphics, verts, triangles);

		_resources[EResourceType::MESH][identifier] = UniquePtr<Resource>(mesh);
		_resources[EResourceType::MESH][identifier]->name = name;

		return handle;
	}

	ResourceHandle<EResourceType::MESH> ResourceManager::getMeshHandle(const std::string_view name)
	{
		for (auto& [indentifier, resource] : _resources[EResourceType::MESH])
		{
			if (resource->name == name)
			{
				ResourceHandle<EResourceType::MESH> handle;
				handle.identifier = indentifier;

				return handle;
			}
		}

		return ResourceHandle<EResourceType::MESH>();
	}

	Mesh* ResourceManager::getMesh(const ResourceHandle<EResourceType::MESH> handle)
	{
		const auto res = _resources[EResourceType::MESH].at(handle.identifier).get();
		return static_cast<Mesh*>(res);
	}
}
