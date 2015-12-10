#ifndef YGGDRASIL_ASSET_HPP
#define YGGDRASIL_ASSET_HPP

#include <iostream>
#include <map>
#include "Resource.hpp"

namespace YG
{
	namespace Core
	{
		class Asset
		{
			public:
				Asset(std::string name)
				{
					m_name = name;
					m_id = sm_id;
					sm_id++;
				}

				virtual void Load()
				{
				}

			protected:
				static unsigned int sm_id;
				unsigned int m_id;
				std::string m_name;
				std::map<std::string, Resource*> m_resources;
		};
	};
};

#endif