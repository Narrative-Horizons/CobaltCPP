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
	
	void Entity::invalidate()
	{
		_id = Identifier::Invalid;
	}

	void Entity::release()
	{
		_reg->release(_id);
		invalidate();
	}

	Entity Registry::create()
	{
		return Entity();
	}

	void Registry::release(const Identifier id)
	{
	}
}