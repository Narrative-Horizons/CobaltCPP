#include <iostream>

#include <cobalt/engine.hpp>
#include <cobalt/window.hpp>
#include <cobalt/input.hpp>

#include <cobalt/graphics/graphicscontext.hpp>

using namespace cobalt;

int main()
{
	WindowCreateInfo createInfo;
	createInfo.width = 1280;
	createInfo.height = 720;
	createInfo.title = "Cobalt Engine";
	createInfo.fullscreen = false;
	createInfo.vsync = true;

	Window* window = new Window(createInfo);

	GraphicsContextCreateInfo gCreateInfo;
	gCreateInfo.api = GraphicsAPI::Vulkan;

	GraphicsContext* context = new GraphicsContext(*window, gCreateInfo);

	while (!window->shouldClose())
	{
		Input::update();

		if (Input::isKeyPressed(COBALT_KEY_ESCAPE))
		{
			window->close();
		}

		window->poll();
		context->present();
	}

	delete context;
	delete window;

	//main(instance, NULL, NULL, cmdShow);
}