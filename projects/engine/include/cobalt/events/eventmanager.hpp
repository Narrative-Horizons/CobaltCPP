#pragma once

#include <unordered_map>
#include <cobalt/events/event.hpp>
#include <cobalt/events/cbfunction.hpp>
#include <cobalt/events/receiver.hpp>

namespace cobalt
{
	typedef void(*callback_func)(AReceiver*, const AEvent&);
	
	class EventManager
	{
		private:
			class IEventCallback
			{
				public:
					virtual ~IEventCallback() = default;
					virtual void operator() (const AEvent* event) = 0;
			};

			template<typename Type>
			struct EventCallback final : IEventCallback
			{
				explicit EventCallback(CbFunction<void(const Type&)>&& callback)
					: callback(callback) { }

				~EventCallback() override = default;

				COBALT_NO_COPY_MOVE(EventCallback)

				void operator() (const AEvent* event) override
				{
					callback(*reinterpret_cast<Type*>(const_cast<AEvent*>(event)));
				}

				CbFunction<void(const Type&)> callback;
			};

		public:
			EventManager() = default;
			~EventManager();

			COBALT_NO_COPY_MOVE(EventManager)

			template<typename EventType, typename ReceiverType>
			void subscribe(ReceiverType* receiver, const callback_func func)
			{
				size_t id = Event<EventType>::getType();
				subscribe(id, receiver, func);
			}

			template<typename EventType, typename ReceiverType>
			void subscribe(ReceiverType* receiver);

			template <typename EventTypeOne, typename EventTypeTwo, typename ... EventTypes, typename ReceiverType>
			void subscribe(ReceiverType* receiver);

			template <typename EventType, typename ReceiverType>
			void unsubscribe(ReceiverType* receiver);

			template <typename ReceiverType>
			void unsubscribeFromAll(ReceiverType* receiver);

			template <typename EventType>
			void send(EventType* event);

			template <typename EventType, typename ... Arguments>
			void send(Arguments && ... args);

			COBALT_NO_DISCARD size_t connectedReceiverCount() const;

			template <typename BaseEventType, typename ... DerivedEventTypes>
			void registerEventTypes();

		private:
			std::unordered_map<size_t, std::vector<std::pair<AReceiver*, IEventCallback*>>> _callbacks;
			std::unordered_map<size_t, std::vector<size_t>> _derivedEventMap;
			std::unordered_map<size_t, size_t> _baseEventMap;

			void _send(const AEvent* event, size_t id);
			void _subscribe(AReceiver* receiver, IEventCallback* cb, size_t id);
			void _unsubscribe(AReceiver* receiver, size_t id);
			void _unsubscribeFromAll(AReceiver* receiver);

			void _registerBaseType(size_t base, size_t derived);
			void _registerDerivedTypes(size_t base, std::vector<size_t>& derived);
	};

	template<typename EventType, typename ReceiverType>
	void EventManager::subscribe(ReceiverType* receiver)
	{
		auto lambda = [=](const EventType& aEvent) {
			receiver->onReceive(aEvent);
		};
		
		IEventCallback* cb = new EventCallback<EventType>(lambda);
		_subscribe(receiver, cb, Event<EventType>::getType());
	}

	template<typename EventTypeOne, typename EventTypeTwo, typename ... EventTypes, typename ReceiverType>
	void EventManager::subscribe(ReceiverType* receiver)
	{
		subscribe<EventTypeOne>(receiver);
		subscribe<EventTypeTwo, EventTypes...>(receiver);
	}

	template<typename EventType, typename ReceiverType>
	void EventManager::unsubscribe(ReceiverType* receiver)
	{
		_unsubscribe(receiver, Event<EventType>::getType());
	}

	template<typename ReceiverType>
	void EventManager::unsubscribeFromAll(ReceiverType* receiver)
	{
		_unsubscribeFromAll(receiver);
	}

	template <typename EventType>
	void EventManager::send(EventType* event)
	{
		_send(event, Event<EventType>::getType());
	}

	template <typename EventType, typename ... Arguments>
	void EventManager::send(Arguments && ... args)
	{
		EventType e(std::forward<Arguments>(args)...);
		send(&e);
	}

	template <typename ... Types>
	struct type_of;

	template <typename T1>
	struct type_of<T1>
	{
		static void get_types(std::vector<size_t>& ids)
		{
			ids.push_back(Event<T1>::getType());
		}
	};

	template <typename T1, typename ... Rest>
	struct type_of<T1, Rest...>
	{
		static void get_types(std::vector<size_t>& ids)
		{
			ids.push_back(Event<T1>::getType());
			type_of<Rest...>::get_types(ids);
		}
	};

	template <typename ... DerivedEventTypes>
	std::vector<size_t> get_event_types()
	{
		std::vector<std::size_t> res;
		type_of<DerivedEventTypes...>::get_types(res);
		return res;
	}

	template<typename BaseEventType, typename ...DerivedEventTypes>
	void EventManager::registerEventTypes()
	{
		if (sizeof...(DerivedEventTypes))
		{
			auto types = get_event_types<DerivedEventTypes...>();
			for (size_t type : types)
			{
				_registerBaseType(Event<BaseEventType>::getType(), type);
			}
			_registerDerivedTypes(Event<BaseEventType>::getType(), types);
		}
		else
		{
			// register single type, no-op
			Event<BaseEventType>::getType();
		}
	}
}
