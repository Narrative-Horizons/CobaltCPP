#include <cassert>
#include <cobalt/events/eventmanager.hpp>

namespace cobalt
{
	EventManager::~EventManager()
	{
		for(auto& cbs : _callbacks)
		{
			for(auto& cb : cbs.second)
			{
				delete cb.second;
			}
		}

		_callbacks.clear();
	}

	size_t EventManager::connectedReceiverCount() const
	{
		size_t count = 0UL;
		for(const auto& [fst, snd] : _callbacks)
		{
			count += snd.size();
		}

		return count;
	}

	void EventManager::_send(const AEvent* event, const size_t id)
	{
		auto handlers = _callbacks.find(id);
		if(handlers != _callbacks.end())
		{
			auto& hs = handlers->second;
			for(auto [fst, snd] : hs)
			{
				snd->operator()(event);
			}
		}

		auto children = _derivedEventMap.find(id);
		if(children != _derivedEventMap.end())
		{
			std::vector<size_t> descendants(children->second);
			size_t iterator = 0;
			while(iterator < descendants.size())
			{
				size_t idx = descendants[iterator++];
				if (event->getId() != idx) continue;

				handlers = _callbacks.find(idx);
				if(handlers != _callbacks.end())
				{
					auto& hs = handlers->second;
					for(auto [fst, snd] : hs)
					{
						snd->operator()(event);
					}

					children = _derivedEventMap.find(idx);
					if(children != _derivedEventMap.end())
					{
						for(auto child : children->second)
						{
							if(std::find(descendants.begin(), descendants.end(), child) != descendants.end())
							{
								assert(false);
								continue;
							}

							descendants.push_back(child);
						}
					}
				}
			}
		}

		auto parent = _baseEventMap.find(id);
		while(parent != _baseEventMap.end())
		{
			handlers = _callbacks.find(parent->second);
			if(handlers != _callbacks.end())
			{
				auto& hs = handlers->second;
				for(auto [fst, snd] : hs)
				{
					snd->operator()(event);
				}
			}

			parent = _baseEventMap.find(parent->second);
		}
	}

	void EventManager::_subscribe(AReceiver* receiver, IEventCallback* cb, size_t id)
	{
		auto eventHandlers = _callbacks.find(id);
		if (eventHandlers != _callbacks.end())
		{
			std::vector<std::pair<AReceiver*, IEventCallback*>> cbs;
			cbs.emplace_back(receiver, cb);
			_callbacks.insert({ id, cbs });
		}
		else
		{
#if defined(_DEBUG)
			for (const auto [fst, snd] : eventHandlers->second)
			{
				assert(fst != receiver);
			}
#endif
			eventHandlers->second.emplace_back(receiver, cb);
		}
	}

	void EventManager::_unsubscribe(AReceiver* receiver, const size_t id)
	{
		auto eventHandlers = _callbacks.find(id);
		if (eventHandlers != _callbacks.end())
		{
			auto it = eventHandlers->second.begin();
			for (auto [fst, snd] : eventHandlers->second)
			{
				if (fst == receiver)
				{
					delete snd;
					break;
				}
				++it;
			}
			eventHandlers->second.erase(it);
		}
	}

	void EventManager::_unsubscribeFromAll(AReceiver* receiver)
	{
		for (auto& [fst, snd] : _callbacks)
		{
			auto it = snd.begin();
			for (auto& handler : snd)
			{
				if (handler.first == receiver)
				{
					delete handler.second;
					break;
				}
				++it;
			}
			if (it != snd.end())
			{
				snd.erase(it);
			}
		}
	}

	void EventManager::_registerBaseType(size_t base, size_t derived)
	{
		_baseEventMap.insert({ derived, base });
	}

	void EventManager::_registerDerivedTypes(size_t base, std::vector<size_t>& derived)
	{
		_derivedEventMap.insert({ base, derived });
	}
}