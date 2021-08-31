#include <fstream>
#include <cobalt/graphics/passes/pbrpass.hpp>
#include <cobalt/graphics/shader.hpp>

namespace cobalt
{
	PBRPass::PBRPass(const UniquePtr<GraphicsContext>& context) : RenderPass(context, "PBR")
	{
		std::ifstream vFile("data/shaders/pbr_vs.hlsl");
		std::string vSource((std::istreambuf_iterator<char>(vFile)),
			std::istreambuf_iterator<char>());

		std::ifstream pFile ("data/shaders/pbr_ps.hlsl");
		std::string pSource((std::istreambuf_iterator<char>(pFile )),
			std::istreambuf_iterator<char>());

		ImmutableSampler imSampler;
		imSampler.name = "textureMap";
		imSampler.shaderStages = ShaderType::PIXEL;

		Sampler sampler;
		imSampler.sampler = sampler;

		ShaderCreateInfo pbrShaderCi;
		pbrShaderCi.name = "PBR Pass";
		pbrShaderCi.vertexSource = vSource;
		pbrShaderCi.pixelSource = pSource;
		pbrShaderCi.cullMode = CullMode::BACK;
		pbrShaderCi.primitiveTopology = PrimitiveTopology::TOPOLOGY_TRIANGLE_LIST;

		ShaderResourceDesc tD;
		tD.name = "textureMap";
		tD.flags = ShaderVariableFlags::NONE;
		tD.shaderStages = ShaderType::PIXEL;
		tD.type = ShaderResourceType::DYNAMIC;

		pbrShaderCi.shaderResources.push_back(tD);
		pbrShaderCi.immutableSamplers.push_back(imSampler);

		_pbrShader = MakeUnique<Shader>(context, pbrShaderCi);
	}

	void PBRPass::render(const FrameInfo frameInfo)
	{
		const UniquePtr<Framebuffer>& renderTo = frameInfo.frameBuffer;
		
		_context->setRenderTarget(renderTo, ResourceStateTransitionMode::TRANSITION);

		const float clearColor[] = { 0, 0, 0, 0 };
		_context->clearRenderTarget(renderTo, 0, clearColor, ResourceStateTransitionMode::TRANSITION);
		_context->clearDepthStencil(renderTo, ClearDepthStencilFlags::DEPTH | ClearDepthStencilFlags::STENCIL, 1.0f, 0, ResourceStateTransitionMode::TRANSITION);

		//_impl->pbrShader->setDataArray(ShaderType::PIXEL, ShaderResourceType::DYNAMIC, "textureMap", textureArrayResource);
	}
}