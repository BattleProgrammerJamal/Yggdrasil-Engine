#ifndef YGGDRASIL_SCENE__HPP
#define YGGDRASIL_SCENE__HPP

#include <iostream>
#include <vector>
#include "Actor.hpp"

namespace YG
{
	namespace Core
	{
		class Scene
		{
			public:
				Scene();
				virtual ~Scene();

				void Add(Actor* actor) { m_children.push_back(actor); }

				std::vector<Actor*> getChildren() const { return m_children; }

				Actor* getByName(std::string name)
				{
					Actor* rslt = 0;
					for (Actor* actor : m_children)
					{
						if (actor->getName() == name)
						{
							return actor;
						}
					}
					return rslt;
				}

			protected:
				std::vector<Actor*> m_children;
		};
	};
}

#endif