#ifndef YGGDRASIL_ACTOR_HPP
#define YGGDRASIL_ACTOR_HPP

#include <iostream>
#include <vector>

namespace YG
{
	class Actor
	{
		public:
			Actor(std::string name = "Actor");
			virtual ~Actor();

			std::string getName() const { return m_name; }
			void setName(const std::string& name) { m_name = name; }

			Actor* getParent() const { return m_parent; }

		protected:
			Actor* m_parent;
			std::string m_name;
	};
};

#endif