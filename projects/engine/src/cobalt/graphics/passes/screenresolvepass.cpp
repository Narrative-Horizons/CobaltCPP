#include <fstream>
#include <cobalt/graphics/passes/screenresolvepass.hpp>
#include <cobalt/graphics/shader.hpp>

namespace cobalt
{
	ScreenResolvePass::ScreenResolvePass(GraphicsContext& context) : RenderPass(context, "ScreenResolvePass")
	{
		_sourceBuffer = nullptr;
		_sourceIndex = 0;
		
		float screenVertices[] = {
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		uint32_t screenIndices[] = {
			2, 1, 0, 0, 3, 2
		};

		_vertexBuffer = MakeUnique<VertexBuffer>(context, screenVertices, sizeof(screenVertices));
		_indexBuffer = MakeUnique<IndexBuffer>(context, screenIndices, sizeof(screenIndices));

		std::ifstream rVFile("data/shaders/resolve_vs.hlsl");
		std::string rVSource((std::istreambuf_iterator<char>(rVFile)),
			std::istreambuf_iterator<char>());

		std::ifstream rPFile("data/shaders/resolve_ps.hlsl");
		std::string rPSource((std::istreambuf_iterator<char>(rPFile)),
			std::istreambuf_iterator<char>());

		ImmutableSampler imSampler;
		imSampler.name = "framebuffer";
		imSampler.shaderStages = ShaderType::PIXEL;

		Sampler sampler;
		imSampler.sampler = sampler;

		ShaderCreateInfo resolveShaderCi;
		resolveShaderCi.name = "Resolve Pass";
		resolveShaderCi.vertexSource = rVSource;
		resolveShaderCi.pixelSource = rPSource;
		resolveShaderCi.cullMode = CullMode::BACK;
		resolveShaderCi.primitiveTopology = PrimitiveTopology::TOPOLOGY_TRIANGLE_LIST;

		ShaderResourceDesc tD;
		tD.name = "tex";
		tD.flags = ShaderVariableFlags::NONE;
		tD.shaderStages = ShaderType::PIXEL;
		tD.type = ShaderResourceType::DYNAMIC;
		
		resolveShaderCi.shaderResources.push_back(tD);
		resolveShaderCi.immutableSamplers.push_back(imSampler);

		 _resolveShader = MakeUnique<Shader>(context, resolveShaderCi);
		_screenBuffers.push_back(_vertexBuffer.get());
	}

	void ScreenResolvePass::setInputTexture(const UniquePtr<Framebuffer> buffer, const uint32_t index)
	{
		_sourceBuffer = buffer.get();
		_sourceIndex = index;
	}

	void ScreenResolvePass::render(const FrameInfo frameInfo)
	{
		const UniquePtr<Framebuffer>& renderTo = frameInfo.frameBuffer;

		_context.setRenderTarget(renderTo, ResourceStateTransitionMode::TRANSITION);

		const float clearColor[] = { 0, 0, 0, 0 };
		_context.clearRenderTarget(renderTo, 0, clearColor, ResourceStateTransitionMode::TRANSITION);
		_context.clearDepthStencil(renderTo, ClearDepthStencilFlags::DEPTH | ClearDepthStencilFlags::STENCIL, 1.0f, 0, ResourceStateTransitionMode::TRANSITION);

		uint32_t offset = 0;

		_context.setVertexBuffers(0, _screenBuffers, &offset, ResourceStateTransitionMode::TRANSITION, SetVertexBufferFlags::RESET);
		_context.setIndexBuffer(*_indexBuffer, 0, ResourceStateTransitionMode::TRANSITION);

		_resolveShader->setData(ShaderType::PIXEL, ShaderResourceType::DYNAMIC, "tex", *_sourceBuffer, _sourceIndex);

		_context.setPipelineState(*_resolveShader);
		_context.commitShaderResources(*_resolveShader, ResourceStateTransitionMode::TRANSITION);

		DrawIndexedAttributes screenAttr;
		screenAttr.indexType = ValueType::UINT32;
		screenAttr.numIndices = 6;
		screenAttr.flags = DrawFlags::VERIFY_ALL;

		_context.drawIndexed(screenAttr);
	}
}