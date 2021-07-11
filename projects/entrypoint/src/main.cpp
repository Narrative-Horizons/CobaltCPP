#include <fstream>
#include <iostream>

#include <cobalt/containers/smartpointers.hpp>
#include <cobalt/window.hpp>
#include <cobalt/input.hpp>

#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/graphics/shader.hpp>
#include <cobalt/graphics/vertexbuffer.hpp>
#include <cobalt/graphics/indexbuffer.hpp>

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
	
	std::ifstream vFile("data/shaders/triangle_vs.hlsl");
	std::string vSource((std::istreambuf_iterator<char>(vFile)),
		std::istreambuf_iterator<char>());

	std::ifstream pFile("data/shaders/triangle_ps.hlsl");
	std::string pSource((std::istreambuf_iterator<char>(pFile)),
		std::istreambuf_iterator<char>());
	
	ShaderCreateInfo shaderCi;
	shaderCi.name = "PBR";
	shaderCi.vertexSource = vSource;
	shaderCi.pixelSource = pSource;
	shaderCi.cullMode = CullMode::BACK;
	shaderCi.primitiveTopology = PrimitiveTopology::TOPOLOGY_TRIANGLE_LIST;

	std::unique_ptr<Shader> shader = std::make_unique<Shader>(*context, shaderCi);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	uint32_t indices[] = {
		2, 1, 0
	};

	std::unique_ptr<VertexBuffer> vertexBuffer = std::make_unique<VertexBuffer>(*context, vertices, sizeof(vertices));
	std::unique_ptr<IndexBuffer> indexBuffer = std::make_unique<IndexBuffer>(*context, indices, sizeof(indices));

	std::vector<VertexBuffer*> buffers;
	buffers.push_back(vertexBuffer.get());
	uint32_t offset = 0;
	
	while (!window->shouldClose())
	{
		Input::update();

		if (Input::isKeyPressed(COBALT_KEY_ESCAPE))
		{
			window->close();
		}

		context->setRenderTarget(nullptr, ResourceStateTransitionMode::TRANSITION);
		
		const float clearColor[] = { 0.350f, 0.350f, 0.350f, 1.0f };
		context->clearRenderTarget(nullptr, 0, clearColor, ResourceStateTransitionMode::TRANSITION);
		context->clearDepthStencil(nullptr, ClearDepthStencilFlags::DEPTH, 1.0f, 0, ResourceStateTransitionMode::TRANSITION);

		context->setVertexBuffers(0, buffers, &offset, ResourceStateTransitionMode::TRANSITION, SetVertexBufferFlags::RESET);
		context->setIndexBuffer(*indexBuffer, 0, ResourceStateTransitionMode::TRANSITION);

		context->setPipelineState(*shader);
		context->commitShaderResources(*shader, ResourceStateTransitionMode::TRANSITION);

		// Draw command
		DrawIndexedAttributes attr;
		attr.indexType = ValueType::UINT32;
		attr.numIndices = 3;
		attr.flags = DrawFlags::VERIFY_ALL;

		context->drawIndexed(attr);

		window->poll();
		context->present();
	}
}