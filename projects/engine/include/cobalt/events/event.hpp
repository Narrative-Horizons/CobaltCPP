#pragma once

#include <cstdint>
#include <cobalt/macros.hpp>

namespace cobalt
{
	class AEvent
	{
		public:
			virtual ~AEvent() = default;

			COBALT_NO_DISCARD size_t getId() const
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
			explicit Event(const size_t id);

			virtual ~Event() override;

			static size_t getType();

		private:
			static size_t _sThisEvent;
	};
	
	template<typename Type>
	Event<Type>::Event()
	{
		_id = Event<Type>::getType();
	}

	template <typename Type>
	Event<Type>::Event(const size_t id)
	{
		_id = id;
	}

	template <typename Type>
	Event<Type>::~Event()
	{
		
	}

	template <typename Type>
	size_t Event<Type>::getType()
	{
		static size_t type = _sId++;
		_sThisEvent = type;

		return type;
	}

	template<typename Type>
	size_t Event<Type>::_sThisEvent = 0;
}
