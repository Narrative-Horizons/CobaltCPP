#pragma once

#include <cstdint>
#include <cobalt/macros.hpp>

namespace cobalt
{
	class AEvent
	{
		public:
			virtual ~AEvent() = default;

			COBALT_NO_DISCARD size_t getId() const noexcept
			{
				return _id;
			}

		protected:
			size_t _id = 0;
			static size_t _sId;
	};

	template<typename Type>
	class Event : public AEvent
	{
		public:
			Event();
			explicit Event(const size_t id) noexcept;
			virtual ~Event() override = default;

			static size_t getType() noexcept;

		private:
			static size_t _sThisEvent;
	};
	
	template<typename Type>
	inline Event<Type>::Event()
	{
		_id = Event<Type>::getType();
	}

	template <typename Type>
	inline Event<Type>::Event(const size_t id) noexcept
	{
		_id = id;
	}

	template <typename Type>
	inline size_t Event<Type>::getType() noexcept
	{
		static size_t type = _sId++;
		_sThisEvent = type;

		return type;
	}

	template<typename Type>
	inline size_t Event<Type>::_sThisEvent = 0;
}
