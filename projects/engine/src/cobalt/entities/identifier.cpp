#include <cobalt/entities/identifier.hpp>

namespace cobalt
{
	Identifier Identifier::Invalid = {
		static_cast<std::uint32_t>(-1),
		static_cast<std::uint32_t>(-1)
	};
}