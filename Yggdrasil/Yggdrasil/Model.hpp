#ifndef YGGDRASIL_MODEL_HPP
#define YGGDRASIL_MODEL_HPP

#include <iostream>
#include <fstream>
#include "Resource.hpp"

namespace YG
{
	namespace Core
	{
		class Model : public Resource
		{
			public:
				Model(std::string path)
					: Resource("MODEL")
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