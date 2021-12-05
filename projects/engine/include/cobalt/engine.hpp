#pragma once

#include <vector>
#include <iostream>

#include <cobalt/containers/smartpointers.hpp>
#include <cobalt/window.hpp>
#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/physics/physics.hpp>
#include <cobalt/resources/resourcemanager.hpp>

namespace cobalt
{
	template<typename Application>
	class Engine
	{
		public:
			static void initialize(UniquePtr<Application>&& app)
			{
				if (_instance == nullptr)
				{
					_instance = new Engine<Application>(move(app));
				}
			}

			static Engine<Application>& instance()
			{
				return *_instance;
			}

			static void destruct()
			{
				delete _instance;
				_instance = nullptr;
			}

			void run()
			{
				_resourceManager = MakeUnique<ResourceManager>(_context);
				_physics = MakeUnique<Physics>();

				_app->initialize();

				while (!_window->shouldClose())
				{
					_app->update();
					_app->render();

					_window->poll();
					_context->present();
				}

				_app->cleanup();
			}

			UniquePtr<Window>& createWindow(WindowCreateInfo info);
			UniquePtr<GraphicsContext>& createGraphicsContext(GraphicsContextCreateInfo info);

			UniquePtr<Window>& getWindow()
			{
				return _window;
			}

			UniquePtr<GraphicsContext>& getGraphicsContext()
			{
				return _context;
			}

			UniquePtr<Physics>& getPhysics()
			{
				return _physics;
			}

		private:
			Engine(UniquePtr<Application>&& app);

			UniquePtr<Application> _app;

			UniquePtr<Window> _window;
			UniquePtr<GraphicsContext> _context;

			UniquePtr<Physics> _physics;

			UniquePtr<ResourceManager> _resourceManager;

			static Engine<Application>* _instance;
	};

	template<typename Application>
	inline Engine<Application>* Engine<Application>::_instance = nullptr;

	template<typename Application>
	inline Engine<Application>::Engine(UniquePtr<Application>&& app)
	{
		_app = move(app);
	}

	template<typename Application>
	inline UniquePtr<Window>& Engine<Application>::createWindow(WindowCreateInfo info)
	{
		_window = MakeUnique<Window>(info);
		return _window;
	}

	template<typename Application>
	inline UniquePtr<GraphicsContext>& Engine<Application>::createGraphicsContext(GraphicsContextCreateInfo info)
	{
		_context = MakeUnique<GraphicsContext>(*_window, info);
		return _context;
	}
}