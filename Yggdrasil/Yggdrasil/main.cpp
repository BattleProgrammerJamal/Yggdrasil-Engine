#include "main.hpp"

using namespace std;
using namespace YG;
using namespace Core;

Renderer *renderer;
Camera *camera;
Scene *scene;

vector<string> shaders = { "Assets/shaders/ppGrayscale.fs", "Assets/shaders/ppInvert.fs", "Assets/shaders/ppSobel.fs", "Assets/shaders/ppEdge.fs" };
unsigned int shaderIndex = 0;

struct KeyEvent : public OnKeyPress
{
	void operator()(sf::Keyboard::Key key)
	{
		if (key == sf::Keyboard::P)
		{
			renderer->enablePostProcess(!renderer->isPostProcessEnabled());
		}

		if (key == sf::Keyboard::G)
		{
			renderer->setPostProcessShader(shaders[shaderIndex]);
			shaderIndex = (shaderIndex == shaders.size() - 1) ? 0 : shaderIndex + 1;
		}
	}
};

int main(int argc, char **argv)
{
	unsigned int width = 1024, height = 768;
	renderer = new Renderer(width, height, "OpenGL Stochastique LOL");
	scene = new Scene();
	camera = new Core::Camera(45.0f, (float)(width / height), 0.1f, 10000.0f);
	camera->eye = Math::Vector3(0.0f, 1.0f, -40.0f);
	renderer->fog_enabled = true;

	renderer->addLight(new Core::Light(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.5f, -0.5f, -1.0f), Math::Color(1.0f, 1.0f, 1.0f), 1.0f))
		.addLight(new Core::Light(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.5f, 0.5f, -1.0f), Math::Color(1.0f, 1.0f, 1.0f), 5.0f))
		.addLight(new Core::Light(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(4.5f, 0.5f, -10.0f), Math::Color(1.0f, 0.0f, 1.0f), 1.0f))
		.addLight(new Core::Light(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(12.0f, 0.5f, 5.0f), Math::Color(0.0f, 1.0f, 1.0f), 1.0f))
		.addLight(new Core::Light(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(-0.5f, -5.5f, -1.0f), Math::Color(1.0f, 1.0f, 0.0f), 1.0f));
	
	Core::Material *material = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 0.0f, 0.0f), Math::Color(1.0f, 1.0f, 1.0f), 80.0f);
	material->ambientIntensity = 0.5f;
	material->loadTexture("Assets/textures/lava1.jpg");

	Core::Material *material2 = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(0.0f, 1.0f, 1.0f), Math::Color(1.0f, 1.0f, 1.0f), 80.0f);
	material2->ambientIntensity = 0.1f;
	material2->loadTexture("Assets/textures/lava2.jpg");

	Core::Material *material3 = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 0.0f, 0.0f), Math::Color(1.0f, 0.5f, 0.3f), 40.0f);
	material3->ambientIntensity = 0.5f;
	material3->loadTexture("Assets/textures/metal.jpg");

	Core::Mesh *sphere = new Core::Mesh(new Core::SphereGeometry(1.0f, 128, 128), material);
	sphere->transform.Translate(Math::Vector3(0.0f, 3.0f, 0.0f));
	sphere->setName("Sphere");
	scene->Add(sphere);

	Core::Mesh *sphere2 = new Core::Mesh(new Core::SphereGeometry(1.5f, 128, 128), material);
	sphere2->setName("Sphere2");
	sphere2->transform.Translate(Math::Vector3(4.0f, 3.0f, -1.0f));
	scene->Add(sphere2);

	Core::Mesh *ground = new Core::Mesh(new Core::PlaneGeometry(30.0f), material3);
	ground->transform.rotation.x = Math::Rad(90.0f);
	ground->transform.position.z = 12.0f;
	ground->transform.position.y = 25.0f;
	scene->Add(ground);

	renderer->enablePostProcess(true);
	renderer->addKeypressEvent(new KeyEvent());

	renderer->setSkybox(
		"Assets/skyboxes/multi3/red/bkg3_right1.png",
		"Assets/skyboxes/multi3/red/bkg3_left2.png",
		"Assets/skyboxes/multi3/red/bkg3_top3.png",
		"Assets/skyboxes/multi3/red/bkg3_bottom4.png",
		"Assets/skyboxes/multi3/red/bkg3_back6.png",
		"Assets/skyboxes/multi3/red/bkg3_front5.png"
	);

	while (renderer->render(scene, camera))
	{
		float dt = renderer->clock.getElapsedTime().asMilliseconds() / 1000.0f;
		sphere->transform.position.x = 1.25f * cos(dt);

		sphere2->transform.position.x = -2.25f * cos(dt);
		sphere2->transform.position.z = 1.25f * cos(dt);
	}

	delete renderer;
	delete scene;
	delete camera;
	
	return 0;
}