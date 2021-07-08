#include <fstream>
#include <iostream>

#include <cobalt/window.hpp>
#include <cobalt/input.hpp>

#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/graphics/shader.hpp>

using namespace cobalt;

/*
extern int WINAPI main(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow);

int WINAPI WinMain(HINSTANCE instance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd)
{
	main(instance, NULL, NULL, nShowCmd);
	*/

int main()
{
	WindowCreateInfo createInfo;
	createInfo.width = 1280;
	createInfo.height = 720;
	createInfo.title = "Cobalt Engine";
	createInfo.fullscreen = false;
	createInfo.vsync = true;

	std::unique_ptr<Window> window = std::make_unique<Window>(createInfo);
	
	GraphicsContextCreateInfo gCreateInfo;
	gCreateInfo.api = GraphicsAPI::Vulkan;

	std::unique_ptr<GraphicsContext> context = std::make_unique<GraphicsContext>(*window, gCreateInfo);
	
	std::ifstream vFile("data/shaders/pbr_vs.hlsl");
	std::string vSource((std::istreambuf_iterator<char>(vFile)),
		std::istreambuf_iterator<char>());

	std::ifstream pFile("data/shaders/pbr_ps.hlsl");
	std::string pSource((std::istreambuf_iterator<char>(pFile)),
		std::istreambuf_iterator<char>());
	
	ShaderCreateInfo shaderCi;
	shaderCi.name = "PBR";
	shaderCi.vertexSource = vSource;
	shaderCi.pixelSource = pSource;
	
	std::unique_ptr<Shader> shader = std::make_unique<Shader>(*context, shaderCi);
	
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
}