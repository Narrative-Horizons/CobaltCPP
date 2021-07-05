#include <iostream>

#include <cobalt/engine.hpp>
#include <cobalt/window.hpp>
#include <cobalt/input.hpp>

int main()
{
	cobalt::WindowCreateInfo createInfo;
	createInfo.width = 1280;
	createInfo.height = 720;
	createInfo.title = "Cobalt Engine";
	createInfo.fullscreen = false;
	createInfo.vsync = true;

	cobalt::Window* window = new cobalt::Window(createInfo);

	while (!window->shouldClose())
	{
		cobalt::Input::update();

		if (cobalt::Input::isKeyPressed(COBALT_KEY_ESCAPE))
		{
			window->close();
		}

		window->poll();
		window->refresh();
	}

	//main(instance, NULL, NULL, cmdShow);
}