#ifndef YGGDRASIL_HPP
#define YGGDRASIL_HPP

#include <iostream>
#include "Math.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Matrix4.hpp"
#include "Quaternion.hpp"
#include "Asset.hpp"
#include "File.hpp"
#include "Image.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Geometry.hpp"
#include "Mesh.hpp"
#include "RenderTarget.hpp"
#include "Renderer.hpp"

#define YGGDRASIL_NAME "Yggdrasil Engine 1.0"

namespace YG
{
	class Yggdrasil
	{
		public:
			Yggdrasil(unsigned int width = 800, unsigned int height = 600, const std::string& title = YGGDRASIL_NAME, Core::CAMERA_TYPE projectionType = Core::PERSPECTIVE)
			{
				m_renderer = new Core::Renderer(width, height, title);
				m_scene = new Core::Scene();
				switch (projectionType)
				{
					case Core::PERSPECTIVE:
						m_mainCamera = new Core::Camera(45.0f, (float)(width / height), 0.1f, 10000.0f);
						break;

					case Core::ORTHOGRAPHIC:
						m_mainCamera = new Core::Camera((float)width, (float)height);
						break;

					default:
						m_mainCamera = new Core::Camera(45.0f, (float)(width / height), 0.1f, 10000.0f);
						break;
				}
			}

			~Yggdrasil()
			{
				delete m_scene;
				delete m_mainCamera;
				delete m_renderer;
			}

			Yggdrasil& addActor(Core::Actor* actor)
			{
				m_scene->Add(actor);
				return *this;
			}

			int Run()
			{
				while (m_renderer->render(m_scene, m_mainCamera));
				return 0;
			}

			Core::Renderer* getRenderer() const { return m_renderer; }

			Core::Scene* getScene() const { return m_scene; }

			Core::Camera* getCamera() const { return m_mainCamera; }

		protected:
			Core::Renderer* m_renderer;
			Core::Scene* m_scene;
			Core::Camera* m_mainCamera;
	};
};

#endif