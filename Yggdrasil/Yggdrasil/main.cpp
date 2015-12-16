#include "main.hpp"

using namespace std;
using namespace YG;
using namespace Core;

int main(int argc, char **argv)
{
	unsigned int width = 1024, height = 768;
	Renderer *renderer = new Renderer(width, height, "OpenGL");
	Scene *scene = new Scene();
	Camera *camera = new Core::Camera(45.0f, (float)(width / height), 0.1f, 10000.0f);
	camera->eye = Math::Vector3(0.0f, 0.0f, -10.0f);

	renderer->addLight(new Core::Light(Math::Vector3(1.1f, 10.0f, 10.0f), Math::Color(1.0f, 0.0f, 1.0f)))
		.addLight(new Core::Light(Math::Vector3(0.0f, 0.5f, 1.0f), Math::Color(1.0f, 1.0f, 1.0f), 1.0f))
		.addLight(new Core::Light(Math::Vector3(-0.5f, 0.0f, -1.0f), Math::Color(1.0f, 0.0f, 1.0f)))
		.addLight(new Core::Light(Math::Vector3(0.5f, -0.5f, 1.0f), Math::Color(0.2f, 0.3f, 0.5f)));
	
	Core::Material *material = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 0.0f, 0.0f), Math::Color(1.0f, 1.0f, 1.0f), 80.0f);
	material->ambientIntensity = 0.1f;
	material->loadTexture("Assets/textures/lava1.jpg");

	Core::Material *material2 = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 0.0f, 1.0f), Math::Color(1.0f, 1.0f, 1.0f), 80.0f);
	material2->loadTexture("Assets/textures/lava2.jpg");

	Core::Mesh *sphere = new Core::Mesh(new Core::SphereGeometry(1.0f, 128, 128), material);
	sphere->setName("Sphere");
	scene->Add(sphere);

	Core::Mesh *sphere2 = new Core::Mesh(new Core::SphereGeometry(1.0f, 128, 128), material2);
	sphere2->setName("Sphere2");
	sphere2->transform.Translate(Math::Vector3(1.0f, 0.0f, 1.0f));
	scene->Add(sphere2);

	while (renderer->render(scene, camera))
	{
	}

	delete renderer;
	delete scene;
	delete camera;
	
	return 0;
}