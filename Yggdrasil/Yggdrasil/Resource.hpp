#ifndef YGGDRASIL_RESOURCE_HPP
#define YGGDRASIL_RESOURCE_HPP

#include <iostream>
#include <fstream>

namespace YG
{
	class Resource
	{
		public:
			Resource(std::string name)
			{
				m_name = name;
				m_id = sm_id;
				sm_id++;
			}

			virtual void Load()
			{
			}

			unsigned int getId() const { return m_id; }

			std::string getName() const { return m_name; }
			void setName(const std::string& name) { m_name = name; }

		protected:
			static unsigned int sm_id;
			unsigned int m_id;
			std::string m_name;
	};
};

#endif