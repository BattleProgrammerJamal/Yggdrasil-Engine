#include "Scene.hpp"

using namespace YG;

Scene::Scene()
{
}

Scene::~Scene()
{
	for (Actor* actor : m_children)
	{
		delete actor;
	}
}