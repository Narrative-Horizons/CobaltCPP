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

	class Window final
	{
		public:
			Window() = default;
			explicit Window(const WindowCreateInfo& createInfo);
			~Window();

			COBALT_NO_COPY_MOVE(Window)

			COBALT_NO_DISCARD uint32_t width() const;
			COBALT_NO_DISCARD uint32_t height() const;
			COBALT_NO_DISCARD std::string title() const;

			void hide() const;
			void show() const;
			void refresh() const;
			void poll() const;
			void close();
		
			COBALT_NO_DISCARD bool shouldClose() const;
			COBALT_NO_DISCARD bool vSyncEnabled() const;

			COBALT_NO_DISCARD void* getNativeWindow() const;

		private:
			friend class GraphicsContext;
		
			WindowCreateInfo _createInfo;
			bool _isOpen;

			void* _glfwWindow;
	};
}
