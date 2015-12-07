#ifndef YGGDRASIL_RENDERER_HPP
#define YGGDRASIL_RENDERER_HPP

#include <iostream>
#include <string>
#include "Scene.hpp"
#include "Camera.hpp"

namespace YG
{
	class Renderer
	{
		public:
			Renderer();
			virtual ~Renderer();

			bool render(const Scene *scene, const Camera *camera);

		protected:
	};
};

#endif