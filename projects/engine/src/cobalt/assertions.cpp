#include <cobalt/assertions.hpp>

#include <cassert>

namespace cobalt
{
	void* detail::RequireNotNullImpl(void* ptr)
	{
		assert(ptr != nullptr);
		return ptr;
	}

}
