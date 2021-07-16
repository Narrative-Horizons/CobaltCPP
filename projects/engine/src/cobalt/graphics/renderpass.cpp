#include <cobalt/graphics/renderpass.hpp>

namespace cobalt
{
	RenderPass::RenderPass(const GraphicsContext& context, const std::string& name) : _context(context)
	{
		_name = name;
	}
}