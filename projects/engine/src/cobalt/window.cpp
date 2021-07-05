#include <cobalt/window.hpp>

#include <iostream>

#include <cobalt/input.hpp>

namespace cobalt
{
	Window::Window(WindowCreateInfo createInfo)
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

		glfwSetKeyCallback(_glfwWindow, [](GLFWwindow* window, const int32_t aKey, const int32_t aScanCode, const int32_t aAction, const int32_t aMods)
		{
			switch (aAction)
			{
				case GLFW_PRESS:
				{
					Input::_setKeyPressed(aKey);
					break;
				}
				case GLFW_RELEASE:
				{
					Input::_setKeyReleased(aKey);
					break;
				}
				case GLFW_REPEAT:
				{
					Input::_setKeyPressed(aKey);
					break;
				}
			}
		});
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
		glfwHideWindow(_glfwWindow);
	}

	void Window::show() const
	{
		glfwShowWindow(_glfwWindow);
	}

	void Window::refresh() const
	{
		glfwSwapBuffers(_glfwWindow);
	}

	void Window::poll() const
	{
		glfwPollEvents();
	}

	void Window::close()
	{
		_isOpen = false;
		glfwSetWindowShouldClose(_glfwWindow, true);
	}

	bool Window::shouldClose() const
	{
		return !_isOpen;
	}

	void* Window::getNativeWindow() const
	{
#if defined(PLATFORM_WIN32)
		return (void*)glfwGetWin32Window(_glfwWindow);
#endif	

		return nullptr;
	}
}