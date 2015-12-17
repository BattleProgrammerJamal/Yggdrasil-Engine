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
	camera->eye = Math::Vector3(0.0f, -1.0f, -20.0f);

	renderer->fog_enabled = true;

	renderer->addLight(new Core::Light(Math::Vector3(0.5f, -0.5f, -1.0f), Math::Color(1.0f, 1.0f, 1.0f), 1.0f))
		.addLight(new Core::Light(Math::Vector3(0.5f, -0.5f, -1.0f), Math::Color(1.0f, 1.0f, 1.0f), 5.0f))
		.addLight(new Core::Light(Math::Vector3(-0.5f, 0.5f, -1.0f), Math::Color(1.0f, 0.0f, 1.0f), 1.0f))
		.addLight(new Core::Light(Math::Vector3(1.0f, 0.5f, 1.0f), Math::Color(0.0f, 1.0f, 1.0f), 1.0f))
		.addLight(new Core::Light(Math::Vector3(-0.5f, -0.5f, -1.0f), Math::Color(1.0f, 1.0f, 0.0f), 1.0f));
	
	Core::Material *material = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 0.0f, 0.0f), Math::Color(1.0f, 1.0f, 1.0f), 80.0f);
	material->ambientIntensity = 0.5f;
	material->loadTexture("Assets/textures/lava1.jpg");

	Core::Material *material2 = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(0.0f, 1.0f, 1.0f), Math::Color(1.0f, 1.0f, 1.0f), 80.0f);
	material2->ambientIntensity = 0.1f;
	material2->loadTexture("Assets/textures/lava2.jpg");

	Core::Material *material3 = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 0.3f, 0.3f), Math::Color(1.0f, 1.0f, 1.0f), 100.0f);
	material3->ambientIntensity = 0.5f;
	material3->loadTexture("Assets/textures/metal.jpg");

	Core::Material *material4 = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 0.3f, 0.3f), Math::Color(1.0f, 1.0f, 1.0f), 100.0f);
	material4->ambientIntensity = 0.5f;
	material4->loadTexture("Assets/textures/metal.jpg");

	Core::Mesh *sphere = new Core::Mesh(new Core::SphereGeometry(1.0f, 128, 128), material);
	sphere->transform.Translate(Math::Vector3(0.0f, 3.0f, 0.0f));
	sphere->setName("Sphere");
	scene->Add(sphere);

	Core::Mesh *sphere2 = new Core::Mesh(new Core::SphereGeometry(1.5f, 128, 128), material2);
	sphere2->setName("Sphere2");
	sphere2->transform.Translate(Math::Vector3(4.0f, 3.0f, -1.0f));
	scene->Add(sphere2);

	Core::Mesh *ground = new Core::Mesh(new Core::PlaneGeometry(8.0f), material3);
	ground->transform.rotation.x = Math::Rad(45.0f);
	scene->Add(ground);

	Core::Mesh *wall = new Core::Mesh(new Core::PlaneGeometry(8.0f), material4);
	wall->transform.rotation.x = Math::Rad(-5.0f);
	wall->transform.Translate(Math::Vector3(0.0f, 7.5f, 3.0f));
	scene->Add(wall);

	while (renderer->render(scene, camera))
	{
		static_cast<PhongMaterial*>(material2)->shininess = 100.0f * cos(renderer->deltaTime);
	}

	delete renderer;
	delete scene;
	delete camera;
	
	return 0;
}