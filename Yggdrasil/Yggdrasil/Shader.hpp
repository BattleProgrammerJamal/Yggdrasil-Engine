#ifndef YGGDRASIL_SHADER_HPP
#define YGGDRASIL_SHADER_HPP

#include <iostream>
#include <fstream>
#include "Resource.hpp"

namespace YG
{
	namespace Core
	{
		class Shader : public Resource
		{
			public:
				Shader(std::string path)
					: Resource("SHADER")
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