#ifndef YGGDRASIL_TEXTURE_HPP
#define YGGDRASIL_TEXTURE_HPP

#include <iostream>
#include <fstream>
#include "Resource.hpp"

namespace YG
{
	namespace Core
	{
		class Texture : public Resource
		{
			public:
				Texture(std::string path)
					: Resource("TEXTURE")
				{
				}

				void Load()
				{
				}

			protected:
		};
	};
};

#endif