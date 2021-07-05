#pragma once

#include <string>

#include <cobalt/macros.hpp>

namespace cobalt
{
	struct WindowCreateInfo
	{
		uint32_t width;
		uint32_t height;

		std::string title;

		bool fullscreen;
		bool vsync;
	};

	class Window
	{
		public:
			Window() = default;
			Window(WindowCreateInfo createInfo);
			virtual ~Window() = default;

			COBALT_NO_COPY_MOVE(Window)

			COBALT_NO_DISCARD uint32_t width() const;
			COBALT_NO_DISCARD uint32_t height() const;
			COBALT_NO_DISCARD std::string title() const;

			void hide() const;
			void show() const;
			void refresh() const;
			void poll() const;
			void close();
			bool shouldClose() const;
			bool vSyncEnabled() const;

			void* getNativeWindow() const;

		private:
			WindowCreateInfo _createInfo;
			bool _isOpen;

			void* _glfwWindow;
	};
}
