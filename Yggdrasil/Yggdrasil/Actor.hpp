#ifndef YGGDRASIL_ACTOR_HPP
#define YGGDRASIL_ACTOR_HPP

#include <iostream>
#include <vector>
#include "Transform.hpp"

namespace YG
{
	namespace Core
	{
		class Actor
		{
			public:
				Math::Transform transform;

				Actor(std::string name = "Actor");
				virtual ~Actor();

				std::string getName() const { return m_name; }
				void setName(const std::string& name) { m_name = name; }

				Actor* getParent() const { return m_parent; }
				void setParent(Actor* actor) { m_parent = actor; }

				void addChild(Actor* actor)
				{
					m_children.push_back(actor);
				}

				bool removeChild(std::string name)
				{
					bool found = false;
					std::vector<Actor*>::iterator it;
					for (it = m_children.begin(); it != m_children.end(); ++it)
					{
						if ((*it)->getName() == name)
						{
							found = true;
							break;
						}
					}
					if (found)
					{
						m_children.erase(it, it);
					}
					return found;
				}

				std::vector<Actor*> getChildren() const { return m_children; }

			protected:
				Actor* m_parent;
				std::vector<Actor*> m_children;
				std::string m_name;
		};
	};
};

#endif