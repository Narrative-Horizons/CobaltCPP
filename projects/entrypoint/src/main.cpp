#include <fstream>
#include <iostream>

#include <cobalt/containers/smartpointers.hpp>
#include <cobalt/window.hpp>
#include <cobalt/input.hpp>

#include <cobalt/entities/entity.hpp>

#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/graphics/shader.hpp>
#include <cobalt/graphics/vertexbuffer.hpp>
#include <cobalt/graphics/indexbuffer.hpp>
#include <cobalt/graphics/uniformbuffer.hpp>
#include <cobalt/graphics/image.hpp>
#include <cobalt/graphics/texture.hpp>

#include <cobalt/math/math.hpp>
#include <cobalt/math/gtx/transform.hpp>
#include <cobalt/baseapplication.hpp>

#include <cobalt/engine.hpp>

#include <imgui.h>

using namespace cobalt;

struct CBuffer
{
	math::mat4 model;

	CBuffer()
	{
		model = math::mat4(1.0f);
	}
};

class Sandbox : BaseApplication
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
			gCreateInfo.api = GraphicsAPI::Vulkan;

			auto& engine = Engine<Sandbox>::instance();
			engine.createWindow(createInfo);

			//////////////////////////////////////

			std::ifstream vFile("data/shaders/triangle_vs.hlsl");
			std::string vSource((std::istreambuf_iterator<char>(vFile)),
				std::istreambuf_iterator<char>());

			std::ifstream pFile("data/shaders/triangle_ps.hlsl");
			std::string pSource((std::istreambuf_iterator<char>(pFile)),
				std::istreambuf_iterator<char>());

			auto& context = Engine<Sandbox>::instance().createGraphicsContext(gCreateInfo);
			uniformBuffer = MakeUnique<UniformBuffer>(context, ShaderResourceType::STATIC, sizeof(float) * 16, "myBuffer");

			ShaderCreateInfo shaderCi;
			shaderCi.name = "PBR";
			shaderCi.vertexSource = vSource;
			shaderCi.pixelSource = pSource;
			shaderCi.cullMode = CullMode::BACK;
			shaderCi.primitiveTopology = PrimitiveTopology::TOPOLOGY_TRIANGLE_LIST;
			shaderCi.renderTargetFormats.push_back(TextureFormat::BGRA8_UNORM_SRGB);
			shaderCi.depthTargetFormat = TextureFormat::D32_FLOAT;

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

			shader = MakeUnique<Shader>(context, shaderCi);

			float vertices[] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
			};

			uint32_t indices[] = {
				2, 1, 0, 0, 3, 2
			};

			vertexBuffer = MakeUnique<VertexBuffer>(context, vertices, sizeof(vertices));
			indexBuffer = MakeUnique<IndexBuffer>(context, indices, sizeof(indices));
			
			buffers.push_back(vertexBuffer.get());

			image = MakeUnique<Image>("data/textures/shawn.png");

			TextureCreateInfo texCreateInfo;
			texCreateInfo.name = "Test";
			texCreateInfo.usage = Usage::DYNAMIC;
			texCreateInfo.format = TextureFormat::RGBA8_UNORM_SRGB;
			texCreateInfo.bindFlags = BindFlags::SHADER_RESOURCE;
			texCreateInfo.accessFlags = CPUAccessFlags::WRITE;

			//ResourceManager* manager = ResourceManager::get();
			
			//texHandle = manager->loadTexture("data/textures/shawn.png", "shawn", texCreateInfo);
			//texture = manager->getTexture(texHandle);

			FramebufferCreateInfo bufferCreateInfo;
			bufferCreateInfo.width = 1280;
			bufferCreateInfo.height = 720;
			bufferCreateInfo.renderTargets.push_back(TextureFormat::BGRA8_UNORM_SRGB);
			bufferCreateInfo.depthTarget = TextureFormat::D32_FLOAT;
			renderBuffer = MakeUnique<Framebuffer>(context, bufferCreateInfo);

			float screenVertices[] = {
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
				1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, 0.0f, 0.0f, 1.0f
			};

			uint32_t screenIndices[] = {
				2, 1, 0, 0, 3, 2
			};

			screenVertexBuffer = MakeUnique<VertexBuffer>(context, screenVertices, sizeof(screenVertices));
			screenIndexBuffer = MakeUnique<IndexBuffer>(context, screenIndices, sizeof(screenIndices));

			std::ifstream rVFile("data/shaders/resolve_vs.hlsl");
			std::string rVSource((std::istreambuf_iterator<char>(rVFile)),
				std::istreambuf_iterator<char>());

			std::ifstream rPFile("data/shaders/resolve_ps.hlsl");
			std::string rPSource((std::istreambuf_iterator<char>(rPFile)),
				std::istreambuf_iterator<char>());

			ShaderCreateInfo resolveShaderCi;
			resolveShaderCi.name = "Resolve Pass";
			resolveShaderCi.vertexSource = rVSource;
			resolveShaderCi.pixelSource = rPSource;
			resolveShaderCi.cullMode = CullMode::BACK;
			resolveShaderCi.primitiveTopology = PrimitiveTopology::TOPOLOGY_TRIANGLE_LIST;

			resolveShaderCi.immutableSamplers.push_back(imSampler);

			resolveShaderCi.shaderResources.push_back(tD);

			screenResolveShader = MakeUnique<Shader>(context, resolveShaderCi);

			screenBuffers.push_back(screenVertexBuffer.get());
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

			if (Input::isKeyDown(COBALT_KEY_D))
			{
				cBuffer.model = math::translate(cBuffer.model, math::vec3(0.001f, 0, 0));
			}
		}

		void render() override
		{
			auto& engine = Engine<Sandbox>::instance();
			auto& context = engine.getGraphicsContext();
			context->setRenderTarget(renderBuffer, ResourceStateTransitionMode::TRANSITION);

			const float clearColor[] = { 0.350f, 0.350f, 0.350f, 1.0f };
			context->clearRenderTarget(renderBuffer, 0, clearColor, ResourceStateTransitionMode::TRANSITION);
			context->clearDepthStencil(renderBuffer, ClearDepthStencilFlags::DEPTH, 1.0f, 0, ResourceStateTransitionMode::TRANSITION);

			context->setVertexBuffers(0, buffers, &offset, ResourceStateTransitionMode::TRANSITION, SetVertexBufferFlags::RESET);
			context->setIndexBuffer(*indexBuffer, 0, ResourceStateTransitionMode::TRANSITION);

			uniformBuffer->setData(&cBuffer, ResourceStateTransitionMode::TRANSITION);

			shader->setData(ShaderType::PIXEL, ShaderResourceType::DYNAMIC, "tex", *texture);

			context->setPipelineState(*shader);
			context->commitShaderResources(*shader, ResourceStateTransitionMode::TRANSITION);

			// Draw command
			DrawIndexedAttributes attr;
			attr.indexType = ValueType::UINT32;
			attr.numIndices = 6;
			attr.flags = DrawFlags::VERIFY_ALL;

			context->drawIndexed(attr);

			context->setRenderTarget(nullptr, ResourceStateTransitionMode::TRANSITION);

			context->clearRenderTarget(nullptr, 0, clearColor, ResourceStateTransitionMode::TRANSITION);
			context->clearDepthStencil(nullptr, ClearDepthStencilFlags::DEPTH, 1.0f, 0, ResourceStateTransitionMode::TRANSITION);

			context->setVertexBuffers(0, screenBuffers, &offset, ResourceStateTransitionMode::TRANSITION, SetVertexBufferFlags::RESET);
			context->setIndexBuffer(*screenIndexBuffer, 0, ResourceStateTransitionMode::TRANSITION);

			screenResolveShader->setData(ShaderType::PIXEL, ShaderResourceType::DYNAMIC, "tex", *renderBuffer, 0);

			context->setPipelineState(*screenResolveShader);
			context->commitShaderResources(*screenResolveShader, ResourceStateTransitionMode::TRANSITION);

			DrawIndexedAttributes screenAttr;
			screenAttr.indexType = ValueType::UINT32;
			screenAttr.numIndices = 6;
			screenAttr.flags = DrawFlags::VERIFY_ALL;

			context->drawIndexed(screenAttr);

			int32_t mX, mY;
			Input::getMousePosition(&mX, &mY);

			ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize = ImVec2(1280, 720);
			io.MousePos = ImVec2(static_cast<float>(mX), static_cast<float>(mY));
			io.MouseDown[0] = Input::isMouseDown(COBALT_MOUSE_BUTTON_LEFT);

			ImGui::NewFrame();
			ImGui::Begin("Cobalt");

			ImGui::Text("Cobalt Text UI Test");
			ImGui::End();
			ImGui::Render();
		}

		void cleanup() override
		{

		}

		UniquePtr<UniformBuffer> uniformBuffer;
		UniquePtr<Shader> shader;
		UniquePtr<VertexBuffer> vertexBuffer;
		UniquePtr<IndexBuffer> indexBuffer;
		std::vector<VertexBuffer*> buffers;
		UniquePtr<Image> image;
		UniquePtr<Texture> texture;
		ResourceHandle<EResourceType::TEXTURE_2D> texHandle;
		UniquePtr<Framebuffer> renderBuffer;
		UniquePtr<VertexBuffer> screenVertexBuffer;
		UniquePtr<IndexBuffer> screenIndexBuffer;
		UniquePtr<Shader> screenResolveShader;
		std::vector<VertexBuffer*> screenBuffers;
		CBuffer cBuffer;
		uint32_t offset = 0;
};

ENTRYPOINT(Sandbox)