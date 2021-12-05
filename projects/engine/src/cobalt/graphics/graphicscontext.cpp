#define VMA_IMPLEMENTATION
#define VMA_STATIC_VULKAN_FUNCTIONS 0

#include <cobalt/graphics/graphicscontext.hpp>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace cobalt
{
	GraphicsContext::GraphicsContext(const Window& window, GraphicsContextCreateInfo info)
	{
		_window = &window;

		vkb::InstanceBuilder bldr = vkb::InstanceBuilder()
			.set_app_version(info.appVersion.major, info.appVersion.minor, info.appVersion.patch)
			.set_app_name(info.appName)
			.set_engine_version(info.engineVersion.major, info.engineVersion.minor, info.engineVersion.patch)
			.set_engine_name(info.engineName)
			.require_api_version(info.requiredVersion.major, info.requiredVersion.minor, info.requiredVersion.patch)
			.enable_validation_layers(info.requireValidationLayers);

		for (size_t i = 0; i < info.enabledLayerCount; ++i)
		{
			bldr.enable_layer(info.enabledLayers[i]);
		}

		for (size_t i = 0; i < info.enabledExtensionCount; ++i)
		{
			bldr.enable_extension(info.enabledExtensions[i]);
		}

		if (info.useDefaultDebugger)
		{
			bldr.use_default_debug_messenger();
		}

		const auto instanceResult = bldr.build();
		if (!instanceResult)
		{
			// TODO: Print error and exit program
			exit(-1);
		}

		_instance = instanceResult.value();

		// create surface
		VkSurfaceKHR surface;
		const VkResult surfaceResult = glfwCreateWindowSurface(_instance.instance, static_cast<GLFWwindow*>(_window->_glfwWindow), _instance.allocation_callbacks, &surface);

		if (surfaceResult != VK_SUCCESS)
		{
			destroy_instance(_instance);

			// TODO: Print error and exit program
			exit(-1);
		}

		_surface = surface;

		VkPhysicalDeviceVulkan12Features features = {};
		features.drawIndirectCount = true;

		// select physical device
		vkb::PhysicalDeviceSelector physicalDeviceSelector = vkb::PhysicalDeviceSelector(_instance)
			.prefer_gpu_device_type(vkb::PreferredDeviceType::discrete)
			.set_minimum_version(1, 2)
			.set_desired_version(1, 2)
			.set_required_features_12(features)
			.set_surface(surface);
		const auto physicalDeviceResult = physicalDeviceSelector.select();

		if (!physicalDeviceResult)
		{
			destroy_surface(_instance, _surface);
			destroy_instance(_instance);

			// TODO: Print error and exit program
			exit(-1);
		}
		_physicalDevice = physicalDeviceResult.value();

		const auto deviceResult = vkb::DeviceBuilder(_physicalDevice)
			.build();

		if (!deviceResult)
		{
			destroy_surface(_instance, _surface);
			destroy_instance(_instance);

			// TODO: Print error and exit program
			exit(-1);
		}

		_device = deviceResult.value();

		auto gq = _device.get_queue(vkb::QueueType::graphics);
		if (!gq.has_value())
		{
			destroy_surface(_instance, _surface);
			destroy_instance(_instance);

			// TODO: Print error and exit program
			exit(-1);
		}
		_graphicsQueue = gq.value();

		auto pq = _device.get_queue(vkb::QueueType::present);
		if (!pq.has_value())
		{
			destroy_surface(_instance, _surface);
			destroy_instance(_instance);

			// TODO: Print error and exit program
			exit(-1);
		}

		_presentQueue = pq.value();

		auto cq = _device.get_queue(vkb::QueueType::compute);
		if (!cq.has_value())
		{
			destroy_surface(_instance, _surface);
			destroy_instance(_instance);

			// TODO: Print error and exit program
			exit(-1);
		}

		_computeQueue = cq.value();

		auto tq = _device.get_queue(vkb::QueueType::transfer);
		if (!tq.has_value())
		{
			destroy_surface(_instance, _surface);
			destroy_instance(_instance);

			// TODO: Print error and exit program
			exit(-1);
		}

		_tranferQueue = tq.value();

		_device = deviceResult.value();
		_functionTable = _device.make_table();

		VmaAllocatorCreateInfo allocatorInfo = {};
		allocatorInfo.flags = 0;
		allocatorInfo.device = _device;

		VmaVulkanFunctions funcs = {};
		funcs.vkGetPhysicalDeviceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(_instance.fp_vkGetInstanceProcAddr(
			_instance.instance, "vkGetPhysicalDeviceProperties"));
		funcs.vkGetPhysicalDeviceMemoryProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(_instance.fp_vkGetInstanceProcAddr(
			_instance.instance, "vkGetPhysicalDeviceMemoryProperties"));
		funcs.vkAllocateMemory = _functionTable.fp_vkAllocateMemory;
		funcs.vkFreeMemory = _functionTable.fp_vkFreeMemory;
		funcs.vkMapMemory = _functionTable.fp_vkMapMemory;
		funcs.vkUnmapMemory = _functionTable.fp_vkUnmapMemory;
		funcs.vkFlushMappedMemoryRanges = _functionTable.fp_vkFlushMappedMemoryRanges;
		funcs.vkInvalidateMappedMemoryRanges = _functionTable.fp_vkInvalidateMappedMemoryRanges;
		funcs.vkBindBufferMemory = _functionTable.fp_vkBindBufferMemory;
		funcs.vkBindImageMemory = _functionTable.fp_vkBindImageMemory;
		funcs.vkGetBufferMemoryRequirements = _functionTable.fp_vkGetBufferMemoryRequirements;
		funcs.vkGetImageMemoryRequirements = _functionTable.fp_vkGetImageMemoryRequirements;
		funcs.vkCreateBuffer = _functionTable.fp_vkCreateBuffer;
		funcs.vkDestroyBuffer = _functionTable.fp_vkDestroyBuffer;
		funcs.vkCreateImage = _functionTable.fp_vkCreateImage;
		funcs.vkDestroyImage = _functionTable.fp_vkDestroyImage;
		funcs.vkCmdCopyBuffer = _functionTable.fp_vkCmdCopyBuffer;
		funcs.vkGetBufferMemoryRequirements2KHR = _functionTable.fp_vkGetBufferMemoryRequirements2KHR;
		funcs.vkGetImageMemoryRequirements2KHR = _functionTable.fp_vkGetImageMemoryRequirements2KHR;
		funcs.vkBindBufferMemory2KHR = _functionTable.fp_vkBindBufferMemory2KHR;
		funcs.vkBindImageMemory2KHR = _functionTable.fp_vkBindImageMemory2KHR;
		funcs.vkGetPhysicalDeviceMemoryProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2KHR>(_instance.fp_vkGetInstanceProcAddr(
			_instance.instance, "vkGetPhysicalDeviceMemoryProperties2KHR"));

		allocatorInfo.pVulkanFunctions = &funcs;
		allocatorInfo.instance = _instance;
		allocatorInfo.physicalDevice = _physicalDevice;

		vmaCreateAllocator(&allocatorInfo, &_allocator);

		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.pNext = nullptr;
		poolInfo.queueFamilyIndex = _device.get_queue_index(vkb::QueueType::graphics).value();
		_functionTable.createCommandPool(&poolInfo, _device.allocation_callbacks, &_graphicsPool);

		poolInfo.queueFamilyIndex = _device.get_queue_index(vkb::QueueType::compute).value();
		_functionTable.createCommandPool(&poolInfo, _device.allocation_callbacks, &_computePool);

		poolInfo.queueFamilyIndex = _device.get_queue_index(vkb::QueueType::present).value();
		_functionTable.createCommandPool(&poolInfo, _device.allocation_callbacks, &_presentPool);

		poolInfo.queueFamilyIndex = _device.get_queue_index(vkb::QueueType::transfer).value();
		_functionTable.createCommandPool(&poolInfo, _device.allocation_callbacks, &_transferPool);

		VkPipelineCacheCreateInfo cacheInfo = {};
		cacheInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
		cacheInfo.flags = 0;
		cacheInfo.pNext = nullptr;
		cacheInfo.initialDataSize = 0;
		cacheInfo.pInitialData = nullptr;

		// TODO: Look for pipelinecache file on load, on exit save out the pipeline cache
		_pipelineCache = VK_NULL_HANDLE;
	}

	GraphicsContext::~GraphicsContext()
	{
		destroy_device(_device);
		destroy_surface(_instance, _surface);
		destroy_instance(_instance);
	}

	GraphicsContext::GraphicsContext(GraphicsContext&& other) noexcept
	{
		
	}

	GraphicsContext& GraphicsContext::operator=(GraphicsContext&& other) noexcept
	{
		return *this;
	}


	void GraphicsContext::present()
	{
		
	}

	void GraphicsContext::resize(const uint32_t width, const uint32_t height)
	{
		
	}
}