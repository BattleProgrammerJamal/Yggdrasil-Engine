#include "Renderer.hpp"

using namespace YG;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::render(const Scene *scene, const Camera *camera)
{
	static int event_close = 0;
	++event_close;
	if (event_close == 500) { return false; }

	for (Actor* actor : scene->getChildren())
	{
		std::cout << "Draw " << actor->getName() << std::endl;
	}

	return true;
}