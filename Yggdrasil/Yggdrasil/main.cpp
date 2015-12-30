#include "main.hpp"

using namespace std;
using namespace YG;
using namespace Core;

Renderer *renderer;
Camera *camera;
Scene *scene;

vector<string> shaders = { "Assets/shaders/ppGrayscale.fs", "Assets/shaders/ppInvert.fs", "Assets/shaders/ppSobel.fs", "Assets/shaders/ppEdge.fs" };
unsigned int shaderIndex = 0;
float cameraVelocity = 10.0f;
unsigned int skyboxIndex = 2;

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

		if (key == sf::Keyboard::Up)
		{
			camera->eye.y += cameraVelocity * 0.05f;
		}

		if (key == sf::Keyboard::Down)
		{
			camera->eye.y -= cameraVelocity * 0.05f;
		}

		if (key == sf::Keyboard::Left)
		{
			camera->eye.x -= cameraVelocity * 0.05f;
		}

		if (key == sf::Keyboard::Right)
		{
			camera->eye.x += cameraVelocity * 0.05f;
		}

		if (key == sf::Keyboard::Add)
		{
			camera->eye.z += cameraVelocity * 0.05f;
		}

		if (key == sf::Keyboard::Subtract)
		{
			camera->eye.z -= cameraVelocity * 0.05f;
		}

		if (key == sf::Keyboard::S)
		{
			switch (skyboxIndex)
			{
				case 0:
					renderer->setSkybox(
						DEFAULT_SKYBOX_RIGHT,
						DEFAULT_SKYBOX_LEFT,
						DEFAULT_SKYBOX_TOP,
						DEFAULT_SKYBOX_BOTTOM,
						DEFAULT_SKYBOX_BACK,
						DEFAULT_SKYBOX_FRONT
					);
					break;

				case 1:
					renderer->setSkybox(
						"Assets/skyboxes/multi3/red/bkg3_right1.png",
						"Assets/skyboxes/multi3/red/bkg3_left2.png",
						"Assets/skyboxes/multi3/red/bkg3_top3.png",
						"Assets/skyboxes/multi3/red/bkg3_bottom4.png",
						"Assets/skyboxes/multi3/red/bkg3_back6.png",
						"Assets/skyboxes/multi3/red/bkg3_front5.png"
					);
					break;

				case 2:
					renderer->setSkybox(
						"Assets/skyboxes/multi2/elyvisions/sh_rt.png",
						"Assets/skyboxes/multi2/elyvisions/sh_lf.png",
						"Assets/skyboxes/multi2/elyvisions/sh_up.png",
						"Assets/skyboxes/multi2/elyvisions/sh_dn.png",
						"Assets/skyboxes/multi2/elyvisions/sh_bk.png",
						"Assets/skyboxes/multi2/elyvisions/sh_ft.png"
					);
					break;
			}
			skyboxIndex = (skyboxIndex + 1) % 3;
		}
	}
};

int main(int argc, char **argv)
{
	unsigned int width = 1600, height = 900;
	renderer = new Renderer(width, height, "OpenGL Stochastique LOL");
	scene = new Scene();
	camera = new Core::Camera(45.0f, (float)(width / height), 0.1f, 10000.0f);
	camera->eye = Math::Vector3(0.0f, 1.0f, -10.0f);
	renderer->fog_enabled = true;

	renderer->addLight(new Core::Light(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.5f, 1.5f, -1.0f), Math::Color(1.0f, 1.0f, 1.0f), 1.0f))
		.addLight(new Core::Light(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.5f, 0.5f, -1.0f), Math::Color(1.0f, 1.0f, 1.0f), 5.0f))
		.addLight(new Core::Light(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(-4.5f, -0.5f, -10.0f), Math::Color(1.0f, 0.0f, 1.0f), 1.0f))
		.addLight(new Core::Light(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(2.0f, 2.5f, 5.0f), Math::Color(0.0f, 1.0f, 1.0f), 1.0f))
		.addLight(new Core::Light(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(-0.5f, -5.5f, 1.0f), Math::Color(1.0f, 1.0f, 0.0f), 1.0f));
	
	Core::Material *material = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 0.0f, 0.0f), Math::Color(1.0f, 1.0f, 1.0f), 80.0f);
	material->ambientIntensity = 0.5f;
	material->loadTexture("Assets/textures/lava1.jpg");

	Core::Material *material2 = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(0.0f, 1.0f, 1.0f), Math::Color(1.0f, 1.0f, 1.0f), 80.0f);
	material2->ambientIntensity = 0.1f;
	material2->loadTexture("Assets/textures/17.jpg");
	material2->loadTexture("Assets/textures/water4.jpg");

	Core::Material *material3 = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 0.0f, 0.0f), Math::Color(1.0f, 0.5f, 0.3f), 40.0f);
	material3->ambientIntensity = 0.5f;
	material3->loadTexture("Assets/textures/metal.jpg");

	Core::Mesh *sphere = new Core::Mesh(new Core::SphereGeometry(4.0f, 128, 128), material);
	sphere->transform.Translate(Math::Vector3(0.0f, 0.0f, 0.0f));
	sphere->setName("Sphere");
	scene->Add(sphere);

	Core::Mesh *sphere2 = new Core::Mesh(new Core::SphereGeometry(3.5f, 128, 128), material2);
	sphere2->setName("Sphere2");
	sphere2->transform.Translate(Math::Vector3(4.0f, 0.0f, -3.0f));
	scene->Add(sphere2);

	renderer->enablePostProcess(true);
	renderer->addKeypressEvent(new KeyEvent());

	while (renderer->render(scene, camera))
	{
		float dt = renderer->clock.getElapsedTime().asMilliseconds() / 1000.0f;
		sphere->transform.position.x = 1.25f * cos(dt);
		sphere->transform.position.y = 4.0f * sin(dt);

		sphere2->transform.position.x = -2.25f * -sin(dt);
		sphere2->transform.position.z = 3.25f * cos(dt);
	}

	delete renderer;
	delete scene;
	delete camera;
	
	return 0;
}