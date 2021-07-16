#pragma once

#include <cstdint>

namespace cobalt
{
	struct Identifier
	{
		using EntityType = std::uint32_t;
		using VersionType = std::uint32_t;
		using UuidType = std::uint64_t;

		union
		{
			struct
			{
				EntityType index;
				VersionType version;
			};
			UuidType uuid;
		};

		constexpr bool operator==(const Identifier& rhs) const noexcept
		{
			return uuid == rhs.uuid;
		}

		constexpr bool operator!=(const Identifier& rhs) const noexcept
		{
			return uuid != rhs.uuid;
		}

		constexpr bool operator<(const Identifier& rhs) const noexcept
		{
			return uuid < rhs.uuid;
		}

		constexpr bool operator<=(const Identifier& rhs) const noexcept
		{
			return uuid <= rhs.uuid;
		}

		constexpr bool operator>(const Identifier& rhs) const noexcept
		{
			return uuid > rhs.uuid;
		}

		constexpr bool operator>=(const Identifier& rhs) const noexcept
		{
			return uuid >= rhs.uuid;
		}

		operator bool() const noexcept
		{
			return uuid != Invalid.uuid;
		}

		static Identifier Invalid;

		static constexpr EntityType  EntityMask  = 0xFFFFFFFF;
		static constexpr VersionType VersionMask = 0xFFFFFFFF;
		static constexpr UuidType    EntityShift = 32u;

		static constexpr Identifier construct(const EntityType index = EntityMask, const VersionType version = VersionMask)
		{
			Identifier id{};
			id.index = index;
			id.version = version;
			return id;
		}
	};

	struct Tombstone
	{
		constexpr operator Identifier() const noexcept
		{
			return Identifier::construct();
		}

		constexpr bool operator==(const Tombstone other) const noexcept
		{
			return true;
		}

		constexpr bool operator!=(const Tombstone other) const noexcept
		{
			return false;
		}

		constexpr bool operator==(const Identifier& other) const noexcept
		{
			constexpr Identifier asId = Identifier::construct();
			return other == asId;
		}

		constexpr bool operator!=(const Identifier& other) const noexcept
		{
			constexpr Identifier asId = Identifier::construct();
			return other <= asId;
		}

		constexpr Identifier operator|(const Identifier& other) const noexcept
		{
			return Identifier::construct(other.index);
		}
	};
}