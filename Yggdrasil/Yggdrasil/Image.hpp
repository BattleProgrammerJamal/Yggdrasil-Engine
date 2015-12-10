#ifndef YGGDRASIL_IMAGE_HPP
#define YGGDRASIL_IMAGE_HPP

#include <iostream>
#include <fstream>
#include "Resource.hpp"

namespace YG
{
	namespace Core
	{
		class Image : public Resource
		{
			public:
				Image(std::string path)
					: Resource("IMAGE")
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