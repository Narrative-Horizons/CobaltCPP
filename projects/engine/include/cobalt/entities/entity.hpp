#pragma once

#include <cobalt/entities/identifier.hpp>

#include <cstdint>

namespace cobalt
{
	class Registry;

	class Entity
	{
		public:
			Entity() = default;
			Entity(Registry* registry, Identifier id);
			
			bool operator==(const Entity& rhs) noexcept;
			bool operator!=(const Entity& rhs) noexcept;
			bool operator<(const Entity& rhs) noexcept;
			bool operator<=(const Entity& rhs) noexcept;
			bool operator>(const Entity& rhs) noexcept;
			bool operator>=(const Entity& rhs) noexcept;

			operator bool() const noexcept;
			Identifier id() const noexcept;
			bool valid() const noexcept;
			
			void invalidate();
			void release();
		private:
			Identifier _id;
			Registry* _reg;
	};

	class Registry
	{
		public:
			Entity create();
			void release(const Identifier id);
		private:
			
	};
}
