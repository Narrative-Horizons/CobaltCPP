#include <cobalt/entities/entity.hpp>

namespace cobalt
{
	Entity::Entity(Registry* registry, Identifier id)
		: _id(id), _reg(registry)
	{
	}

	bool Entity::operator==(const Entity& rhs) noexcept
	{
		return _id == rhs._id && _reg == rhs._reg;
	}

	bool Entity::operator!=(const Entity& rhs) noexcept
	{
		return _id != rhs._id || _reg != rhs._reg;
	}

	bool Entity::operator<(const Entity& rhs) noexcept
	{
		return _id < rhs._id;
	}

	bool Entity::operator<=(const Entity& rhs) noexcept
	{
		return _id <= rhs._id;
	}

	bool Entity::operator>(const Entity& rhs) noexcept
	{
		return _id > rhs._id;
	}

	bool Entity::operator>=(const Entity& rhs) noexcept
	{
		return _id >= rhs._id;
	}

	Entity::operator bool() const noexcept
	{
		return valid();
	}

	Identifier Entity::id() const noexcept
	{
		return _id;
	}

	bool Entity::valid() const noexcept
	{
		return _reg->valid(_id);
	}
	
	void Entity::invalidate()
	{
		_id = Identifier::Invalid;
	}

	void Entity::release()
	{
		_reg->release(_id);
		invalidate();
	}

	Registry::~Registry()
	{
		for (auto pool : _memPools)
		{
			if (pool)
			{
				delete pool;
			}
		}
		_memPools.clear();
	}

	Entity Registry::create()
	{
		const auto id = _nextAvailable == Identifier::Invalid ? _createNewId() : _recycleId();
		const auto res = Entity(this, id);
		_events.send<EntityCreatedEvent>(res);
		return res;
	}

	void Registry::release(const Identifier id)
	{
		// For each memory pool, release the entity
		for (const auto pool : _memPools)
		{
			if (pool)
			{
				pool->remove(id);
			}
		}

		const auto identifier = id.index;
		const auto version = id.version + 1; // on release, increment version
		_entities[identifier] = Identifier::construct(_nextAvailable.index, version);
		_nextAvailable = Identifier::construct(identifier, 0);

		_events.send<EntityDestroyedEvent>(Entity(this, id));
	}

	bool Registry::valid(const Identifier id) const noexcept
	{
		const auto idx = id.index;
		return idx < _entities.size() && _entities[idx] == id;
	}

	EventManager& Registry::events() noexcept
	{
		return _events;
	}

	Identifier Registry::_createNewId()
	{
		// Add a new entity
		const auto id = _entities.size();
		const auto version = 0;
		const Identifier identifier = Identifier::construct(static_cast<std::uint32_t>(id), static_cast<std::uint32_t>(version));
		_entities.emplace_back(identifier);
		return identifier;
	}

	Identifier Registry::_recycleId()
	{
		// Recycles an old identifier from the implicit free list
		const auto id = _nextAvailable.index;
		const auto version = _entities[id].version;
		_nextAvailable = _entities[id];
		_entities[id] = Identifier::construct(id, version);
		return _entities[id];
	}

	EntityCreatedEvent::EntityCreatedEvent(const Entity entity)
		: entity(entity)
	{}

	EntityDestroyedEvent::EntityDestroyedEvent(const Entity entity)
		: entity(entity)
	{}
}