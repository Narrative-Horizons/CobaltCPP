#pragma once

#include <cobalt/window.hpp>

#include <cobalt/graphics/graphicsenums.hpp>

#include <VkBootstrap.h>
#include <vma/vk_mem_alloc.h>

namespace cobalt
{
	struct ApiVersion
	{
		unsigned int major;
		unsigned int minor;
		unsigned int patch;
	};
	
	struct GraphicsContextCreateInfo
	{
		ApiVersion appVersion;
		const char* appName;
		ApiVersion engineVersion;
		const char* engineName;
		ApiVersion requiredVersion;
		ApiVersion desiredVersion;
		size_t enabledLayerCount;
		const char** enabledLayers;
		size_t enabledExtensionCount;
		const char** enabledExtensions;
		bool requireValidationLayers;
		bool useDefaultDebugger;
	};

	class GraphicsContext
	{
		public:
			GraphicsContext(const Window& window, GraphicsContextCreateInfo createInfo);
			~GraphicsContext();

			COBALT_NO_COPY(GraphicsContext)

			GraphicsContext(GraphicsContext&& other) noexcept;
			GraphicsContext& operator=(GraphicsContext&& other) noexcept;

			void present();

			void resize(uint32_t width, uint32_t height);

		private:
			const Window* _window;

			vkb::Instance _instance;
			vkb::PhysicalDevice _physicalDevice;
			vkb::Device _device;
			vkb::DispatchTable _functionTable;
			VkSurfaceKHR _surface;
			VmaAllocator _allocator;

			VkQueue _graphicsQueue;
			VkQueue _presentQueue;
			VkQueue _computeQueue;
			VkQueue _tranferQueue;

			VkCommandPool _graphicsPool;
			VkCommandPool _presentPool;
			VkCommandPool _computePool;
			VkCommandPool _transferPool;

			VkPipelineCache _pipelineCache;
	};
}
