#include "main.hpp"

using namespace std;
using namespace YG;
using namespace Core;
using namespace Empathic;

Renderer *renderer;
Camera *camera;
Scene *scene;

vector<string> shaders = { "Assets/shaders/ppGrayscale.fs", "Assets/shaders/ppInvert.fs", "Assets/shaders/ppSobel.fs", "Assets/shaders/ppEdge.fs" };
unsigned int shaderIndex = 0;
float cameraVelocity = 80.0f;

struct KeyEvent : public OnKeyPress
{
	void operator()(sf::Keyboard::Key key)
	{
		if (key == sf::Keyboard::P) { renderer->enablePostProcess(!renderer->isPostProcessEnabled()); }
		if (key == sf::Keyboard::G) { renderer->setPostProcessShader(shaders[shaderIndex]); shaderIndex = (shaderIndex == shaders.size() - 1) ? 0 : shaderIndex + 1; }

		if (key == sf::Keyboard::Up) { camera->eye.y += cameraVelocity * 0.05f; camera->target.y += cameraVelocity * 0.05f; }
		if (key == sf::Keyboard::Down) { camera->eye.y -= cameraVelocity * 0.05f; camera->target.y -= cameraVelocity * 0.05f; }
		if (key == sf::Keyboard::Left) { camera->eye.x += cameraVelocity * 0.05f; camera->target.x += cameraVelocity * 0.05f; }
		if (key == sf::Keyboard::Right) { camera->eye.x -= cameraVelocity * 0.05f; camera->target.x -= cameraVelocity * 0.05f; }

		if (key == sf::Keyboard::Add) { camera->eye.z += cameraVelocity * 0.05f; camera->target.z += cameraVelocity * 0.05f; }
		if (key == sf::Keyboard::Subtract) { camera->eye.z -= cameraVelocity * 0.05f; camera->target.z -= cameraVelocity * 0.05f; }
	}
};

int main(int argc, char **argv)
{
	unsigned int width = 800, height = 600;
	renderer = new Renderer(width, height, "Yggdrasil DEMO");
	scene = new Scene();
	camera = new Core::Camera(45.0f, (float)(width / height), 0.1f, 10000.0f);
	camera->eye = Math::Vector3(0.0f, 5.0f, -50.0f);
	camera->target = Math::Vector3(0.0f, 5.0f, 0.0f);
	renderer->fog_enabled = true;
	renderer->enableSkybox(false);

	renderer->addLight(new Core::DirectionnalLight(Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Math::Color(1.0f, 1.0f, 1.0f), 1.0f));
	renderer->addLight(new Core::PointLight(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Color(1.0f, 0.0f, 0.0f), 1.0f));

	Core::Material *leematerial = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(0.5f, 0.5f, 0.0f), Math::Color(1.0f, 1.0f, 1.0f), 10.0f);
	leematerial->ambientIntensity = 0.05f;
	leematerial->loadTexture("Assets/models/lee-perry-smith-head-scan-obj/Face_Color.jpg");

	Core::Model *modelB = new Core::Model("Assets/models/lee-perry-smith-head-scan-obj/lee-perry-smith-head-scan.obj");
	Core::Mesh *lee = modelB->Instanciate(1);
	lee->renderStyle = GL_TRIANGLES;
	lee->setMaterial(leematerial);
	lee->transform.Scale(Math::Vector3(15.0f, 15.0f, 15.0f));
	lee->transform.rotation.y = Math::Rad(90.0f);
	scene->Add(lee);

	renderer->enablePostProcess(true);
	renderer->addKeypressEvent(new KeyEvent());

	while (renderer->render(scene, camera))
	{
		float dt = renderer->clock.getElapsedTime().asMilliseconds() / 1000.0f;

		static_cast<DirectionnalLight*>(renderer->getLight(0))->direction.x = 2.5f * cos(dt);
		static_cast<DirectionnalLight*>(renderer->getLight(0))->direction.y = 1.25f * sin(dt);
		static_cast<DirectionnalLight*>(renderer->getLight(0))->direction.z = 3.25f * sin(dt);

		lee->transform.rotation.y += 0.005f;
	}

	delete renderer;
	delete scene;
	delete camera;
	
	return 0;
}