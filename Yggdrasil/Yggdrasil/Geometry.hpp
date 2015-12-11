#ifndef YGGDRASIL_GEOMETRY_HPP
#define YGGDRASIL_GEOMETRY_HPP

#include <iostream>
#include "Asset.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace YG
{
	namespace Core
	{
		class Geometry : public Asset
		{
			public:
				Geometry(std::string name)
					: Asset(name)
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