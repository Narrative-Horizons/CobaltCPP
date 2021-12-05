#include <cobalt/containers/smartpointers.hpp>
#include <cobalt/window.hpp>
#include <cobalt/input.hpp>

#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/graphics/image.hpp>

#include <cobalt/baseapplication.hpp>

#include <cobalt/engine.hpp>

using namespace cobalt;

class Sandbox final : BaseApplication
{
	public:
		void initialize() override
		{
			WindowCreateInfo createInfo;
			createInfo.width = 1280;
			createInfo.height = 720;
			createInfo.title = "Cobalt Engine";
			createInfo.fullscreen = false;
			createInfo.vsync = true;

			GraphicsContextCreateInfo gCreateInfo;
			gCreateInfo.appName = "Cobalt Engine - Sandbox";
			gCreateInfo.appVersion = { 1, 0, 0 };
			gCreateInfo.desiredVersion = { 1, 2, 0 };
			gCreateInfo.enabledExtensionCount = 0;
			gCreateInfo.enabledExtensions = {};
			gCreateInfo.enabledLayerCount = 0;
			gCreateInfo.enabledLayers = {};
			gCreateInfo.engineName = "Cobalt";
			gCreateInfo.engineVersion = { 1, 0, 0 };
			gCreateInfo.requiredVersion = { 1, 2, 0 };
			gCreateInfo.requireValidationLayers = true;
			gCreateInfo.useDefaultDebugger = true;

			auto& engine = Engine<Sandbox>::instance();
			engine.createWindow(createInfo);
			engine.createGraphicsContext(gCreateInfo);
		}

		void update() override
		{
			auto& engine = Engine<Sandbox>::instance();
			auto& window = engine.getWindow();

			Input::update();

			if (Input::isKeyPressed(COBALT_KEY_ESCAPE))
			{
				window->close();
			}
		}

		void render() override
		{
			auto& engine = Engine<Sandbox>::instance();
			auto& context = engine.getGraphicsContext();
		}

		void cleanup() override
		{

		}
};

ENTRYPOINT(Sandbox)