#include <cobalt/graphics/renderpass.hpp>

namespace cobalt
{
	RenderPass::RenderPass(GraphicsContext& context, const std::string& name) : _context(context)
	{
		_name = name;
	}
}