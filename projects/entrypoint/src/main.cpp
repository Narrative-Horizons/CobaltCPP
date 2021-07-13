#include <fstream>
#include <iostream>

#include <cobalt/containers/smartpointers.hpp>
#include <cobalt/window.hpp>
#include <cobalt/input.hpp>

#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/graphics/shader.hpp>
#include <cobalt/graphics/vertexbuffer.hpp>
#include <cobalt/graphics/indexbuffer.hpp>
#include <cobalt/graphics/uniformbuffer.hpp>
#include <cobalt/graphics/shaderstoragebuffer.hpp>
#include <cobalt/graphics/image.hpp>
#include <cobalt/graphics/texture.hpp>

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

struct CBuffer
{
	float buffer[16];

	CBuffer()
	{
		for (float& i : buffer)
		{
			i = 0.0f;
		}
	}
};

int main()
{
	WindowCreateInfo createInfo;
	createInfo.width = 1280;
	createInfo.height = 720;
	createInfo.title = "Cobalt Engine";
	createInfo.fullscreen = false;
	createInfo.vsync = true;

	UniquePtr<Window> window = MakeUnique<Window>(createInfo);
	
	GraphicsContextCreateInfo gCreateInfo;
	gCreateInfo.api = GraphicsAPI::Vulkan;

	UniquePtr<GraphicsContext> context = MakeUnique<GraphicsContext>(*window, gCreateInfo);
	
	std::ifstream vFile("data/shaders/triangle_vs.hlsl");
	std::string vSource((std::istreambuf_iterator<char>(vFile)),
		std::istreambuf_iterator<char>());

	std::ifstream pFile("data/shaders/triangle_ps.hlsl");
	std::string pSource((std::istreambuf_iterator<char>(pFile)),
		std::istreambuf_iterator<char>());

	UniquePtr<UniformBuffer> uniformBuffer = MakeUnique<UniformBuffer>(*context, ShaderResourceType::STATIC, sizeof(float) * 16, "myBuffer");
	
	ShaderCreateInfo shaderCi;
	shaderCi.name = "PBR";
	shaderCi.vertexSource = vSource;
	shaderCi.pixelSource = pSource;
	shaderCi.cullMode = CullMode::BACK;
	shaderCi.primitiveTopology = PrimitiveTopology::TOPOLOGY_TRIANGLE_LIST;

	ImmutableSampler imSampler;
	imSampler.name = "tex";
	imSampler.shaderStages = ShaderType::PIXEL;

	Sampler sampler;
	imSampler.sampler = sampler;
	
	shaderCi.immutableSamplers.push_back(imSampler);
	
	ShaderResourceDesc uD;
	uD.name = "myBuffer";
	uD.flags = ShaderVariableFlags::NONE;
	uD.shaderStages = ShaderType::VERTEX;
	uD.type = ShaderResourceType::STATIC;
	uD.resource = uniformBuffer.get();
	shaderCi.shaderResources.push_back(uD);


	ShaderResourceDesc tD;
	tD.name = "tex";
	tD.flags = ShaderVariableFlags::NONE;
	tD.shaderStages = ShaderType::PIXEL;
	tD.type = ShaderResourceType::DYNAMIC;
	shaderCi.shaderResources.push_back(tD);
	
	UniquePtr<Shader> shader = MakeUnique<Shader>(*context, shaderCi);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.5f, 1.0f
	};

	uint32_t indices[] = {
		2, 1, 0
	};

	UniquePtr<VertexBuffer> vertexBuffer = MakeUnique<VertexBuffer>(*context, vertices, sizeof(vertices));
	UniquePtr<IndexBuffer> indexBuffer = MakeUnique<IndexBuffer>(*context, indices, sizeof(indices));

	std::vector<VertexBuffer*> buffers;
	buffers.push_back(vertexBuffer.get());
	uint32_t offset = 0;

	CBuffer cBuffer;

	cBuffer.buffer[0] = 1.0f;
	cBuffer.buffer[5] = 1.0f;
	cBuffer.buffer[10] = 1.0f;
	cBuffer.buffer[15] = 1.0f;

	UniquePtr<Image> image = MakeUnique<Image>("data/textures/shawn.png");
	
	TextureCreateInfo texCreateInfo;
	texCreateInfo.name = "Test";
	texCreateInfo.usage = Usage::DYNAMIC;
	texCreateInfo.format = TextureFormat::RGBA8_UNORM_SRGB;
	texCreateInfo.bindFlags = BindFlags::SHADER_RESOURCE;
	texCreateInfo.accessFlags = CPUAccessFlags::WRITE;
	
	UniquePtr<Texture> texture = MakeUnique<Texture>(*context, *image, texCreateInfo);
	
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

		uniformBuffer->setData(&cBuffer, ResourceStateTransitionMode::TRANSITION);

		shader->setData(ShaderType::PIXEL, ShaderResourceType::DYNAMIC, "tex", *texture);
		
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