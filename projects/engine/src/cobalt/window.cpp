#include <cobalt/window.hpp>

#include <iostream>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <cobalt/input.hpp>

namespace cobalt
{
	Window::Window(const WindowCreateInfo& createInfo)
	{
		_createInfo = createInfo;

		if (!glfwInit())
		{
			std::cerr << "Failed to initialize GLFW" << std::endl;
			return;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		_glfwWindow = glfwCreateWindow(_createInfo.width, _createInfo.height, _createInfo.title.c_str(), nullptr, nullptr);
		if (!_glfwWindow)
		{
			std::cerr << "Failed to create GLFW window" << std::endl;
			return;
		}

		_isOpen = true;

		glfwSetKeyCallback(static_cast<GLFWwindow*>(_glfwWindow), [](GLFWwindow* window, const int32_t key, const int32_t scanCode, const int32_t action, const int32_t mods)
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					Input::_setKeyPressed(key);
					break;
				}
				case GLFW_RELEASE:
				{
					Input::_setKeyReleased(key);
					break;
				}
				case GLFW_REPEAT:
				{
					Input::_setKeyPressed(key);
					break;
				}
				default: break;
			}
		});

		glfwSetMouseButtonCallback(static_cast<GLFWwindow*>(_glfwWindow), [](GLFWwindow* window, const int32_t button, const int32_t action, const int32_t mods)
		{
			switch(action)
			{
				case GLFW_PRESS:
				{
					Input::_setMousePressed(button);
					break;
				}
				case GLFW_RELEASE:
				{
					Input::_setMouseReleased(button);
					break;
				}
				case GLFW_REPEAT:
				{
					Input::_setMousePressed(button);
					break;
				}
				default: break;
			}
		});

		glfwSetCursorPosCallback(static_cast<GLFWwindow*>(_glfwWindow), [](GLFWwindow* window, double xpos, double ypos)
		{
			Input::_setMousePosition(static_cast<int32_t>(xpos), static_cast<int32_t>(ypos));
		});
	}

	Window::~Window()
	{
		glfwDestroyWindow(static_cast<GLFWwindow*>(_glfwWindow));
		glfwTerminate();
	}

	uint32_t Window::width() const
	{
		return _createInfo.width;
	}

	uint32_t Window::height() const
	{
		return _createInfo.height;
	}

	std::string Window::title() const
	{
		return _createInfo.title;
	}

	void Window::hide() const
	{
		glfwHideWindow(static_cast<GLFWwindow*>(_glfwWindow));
	}

	void Window::show() const
	{
		glfwShowWindow(static_cast<GLFWwindow*>(_glfwWindow));
	}

	void Window::refresh() const
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(_glfwWindow));
	}

	void Window::poll() const
	{
		glfwPollEvents();
	}

	void Window::close()
	{
		_isOpen = false;
		glfwSetWindowShouldClose(static_cast<GLFWwindow*>(_glfwWindow), true);
	}

	bool Window::shouldClose() const
	{
		return !_isOpen || glfwWindowShouldClose(static_cast<GLFWwindow*>(_glfwWindow));
	}

	bool Window::vSyncEnabled() const
	{
		return _createInfo.vsync;
	}

	void* Window::getNativeWindow() const
	{
#if defined(PLATFORM_WIN32)
		return static_cast<void*>(glfwGetWin32Window(static_cast<GLFWwindow*>(_glfwWindow)));
#else
#error Platform not defined/unsupported
#endif
	}
}