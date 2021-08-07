#pragma once

#include <vector>

#include <cobalt/containers/smartpointers.hpp>
#include <cobalt/window.hpp>
#include <cobalt/graphics/graphicscontext.hpp>

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

		private:
			Engine(UniquePtr<Application>&& app);

			UniquePtr<Application> _app;

			UniquePtr<Window> _window;
			UniquePtr<GraphicsContext> _context;

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