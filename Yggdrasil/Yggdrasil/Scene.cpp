#include "Scene.hpp"

using namespace YG;
using namespace Core;

Scene::Scene()
{
}

Scene::~Scene()
{
	for (Actor* actor : m_children)
	{
		//delete actor;
	}
}