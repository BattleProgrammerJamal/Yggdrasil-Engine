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
			camera->target.y += cameraVelocity * 0.05f;
		}

		if (key == sf::Keyboard::Down)
		{
			camera->eye.y -= cameraVelocity * 0.05f;
			camera->target.y -= cameraVelocity * 0.05f;
		}

		if (key == sf::Keyboard::Left)
		{
			camera->eye.x += cameraVelocity * 0.05f;
			camera->target.x += cameraVelocity * 0.05f;
		}

		if (key == sf::Keyboard::Right)
		{
			camera->eye.x -= cameraVelocity * 0.05f;
			camera->target.x -= cameraVelocity * 0.05f;
		}

		if (key == sf::Keyboard::Add)
		{
			camera->eye.z += cameraVelocity * 0.05f;
			camera->target.z += cameraVelocity * 0.05f;
		}

		if (key == sf::Keyboard::Subtract)
		{
			camera->eye.z -= cameraVelocity * 0.05f;
			camera->target.z -= cameraVelocity * 0.05f;
		}
	}
};

struct TestEmotionnalAction : public EmotionnalAction
{
	public:
		TestEmotionnalAction()
			: EmotionnalAction()
		{
		}

		void init()
		{
			m_emotions.push_back(new Emotion(new EmotionnalState("Happiness"), 0.5f));
			m_emotions.push_back(new Emotion(new EmotionnalState("Sadness"), 0.8f));
			m_emotions.push_back(new Emotion(new EmotionnalState("Hatred"), 0.1f));
			m_emotions.push_back(new Emotion(new EmotionnalState("Fear"), 0.15f));
		}

		Emotion* emit()
		{
			Emotion *e = 0;

			if (m_emotions.at(0)->getValue() > m_emotions.at(1)->getValue() && m_emotions.at(0)->getValue() > m_emotions.at(2)->getValue())
			{
				e = m_emotions.at(0);
			}
			else
			{
				if (m_emotions.at(2)->getValue() > m_emotions.at(0)->getValue() && m_emotions.at(1)->getValue() > m_emotions.at(0)->getValue() || m_emotions.at(3)->getValue() > m_emotions.at(0)->getValue())
				{
					e = m_emotions.at(2);
				}
				else
				{
					if (m_emotions.at(3)->getValue() > m_emotions.at(1)->getValue())
					{
						e = m_emotions.at(1);
					}
					else
					{
						e = m_emotions.at(2);
					}
				}
			}

			return e;
		}
};

int main(int argc, char **argv)
{
	/*
	EmotionnalStateMachine esm;
	esm << new TestEmotionnalAction() << new EmotionnalAction();
	
	for (unsigned int i = 0; i < 10; ++i)
	{
		esm.update();
	}

	Emotion current = *esm.getCurrent();
	cout << "Current emotion : " << current << endl;

	system("PAUSE");
	*/
	
	unsigned int width = 1600, height = 900;
	renderer = new Renderer(width, height, "Yggdrasil DEMO");
	scene = new Scene();
	camera = new Core::Camera(45.0f, (float)(width / height), 0.1f, 10000.0f);
	camera->eye = Math::Vector3(0.0f, 5.0f, -50.0f);
	camera->target = Math::Vector3(0.0f, 5.0f, 0.0f);
	renderer->fog_enabled = true;

	renderer->addLight(new Core::DirectionnalLight(Math::Vector3(0.0f, 1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Math::Color(1.0f, 1.0f, 1.0f), 1.0f));
	renderer->addLight(new Core::DirectionnalLight(Math::Vector3(0.0f, 0.5f, 1.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Math::Color(1.0f, 1.0f, 1.0f), 1.0f));
	renderer->addLight(new Core::DirectionnalLight(Math::Vector3(0.5f, -1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Math::Color(1.0f, 1.0f, 1.0f), 10.0f));
	renderer->addLight(new Core::PointLight(Math::Vector3(0.0f, 10.0f, 0.0f), Math::Color(1.0f, 0.0f, 0.0f), 1.0f));

	for (unsigned int i = 0; i < MAXIMUM_LIGHT; ++i)
	{
		Light *L = renderer->getLight(i);
		if (!L) { continue; }

		L->showGizmo = true;
	}

	Core::Material *material = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(0.5f, 0.5f, 0.0f), Math::Color(1.0f, 1.0f, 1.0f), 80.0f);
	material->ambientIntensity = 0.05f;
	static_cast<PhongMaterial*>(material)->specularIntensity = 30.0f;
	material->loadTexture("Assets/models/Stormtrooper/Stormtrooper_D.tga");

	Core::Material *material2 = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(0.5f, 0.5f, 0.0f), Math::Color(1.0f, 1.0f, 1.0f), 10.0f);
	material2->ambientIntensity = 0.05f;
	static_cast<PhongMaterial*>(material2)->specularIntensity = 3.0f;
	material2->loadTexture("Assets/textures/a.jpg");
	material2->repeat.set(30.0f, 20.0f);

	Core::Model *modelA = new Core::Model("Assets/models/Stormtrooper/Stormtrooper.obj");
	for (unsigned int i = 0; i < 5; ++i)
	{
		for (unsigned int j = 0; j < 5; ++j)
		{
			Core::Mesh *mesh = modelA->Instanciate(0);
			mesh->setMaterial(material);
			mesh->transform.position.x = i * 5.0f;
			mesh->transform.position.z = j * 2.0f;
			mesh->transform.rotation.y = Math::Rad(90.0f);
			mesh->transform.Scale(Math::Vector3(5.0f, 5.0f, 5.0f));
			mesh->renderStyle = GL_TRIANGLES;
			scene->Add(mesh);
		}
	}

	Core::Mesh *wall = new Core::Mesh(new Core::SphereGeometry(5000.0f, 64, 64), material2);
	scene->Add(wall);

	/*
	Core::Mesh *ground = new Core::Mesh(new Core::TerrainGeometry(10.0f, 10.0f, 10, 10), material);
	ground->transform.Scale(Math::Vector3(15.0f, 15.0f, 15.0f));
	scene->Add(ground);
	*/

	renderer->enablePostProcess(true);
	renderer->addKeypressEvent(new KeyEvent());
	
	renderer->setSkybox(
		"Assets/skyboxes/2/redeclipse_rt.png",
		"Assets/skyboxes/2/redeclipse_lf.png",
		"Assets/skyboxes/2/redeclipse_up.png",
		"Assets/skyboxes/2/redeclipse_dn.png",
		"Assets/skyboxes/2/redeclipse_bk.png",
		"Assets/skyboxes/2/redeclipse_ft.png"
	);

	while (renderer->render(scene, camera))
	{
		float dt = renderer->clock.getElapsedTime().asMilliseconds() / 1000.0f;
	}

	delete renderer;
	delete scene;
	delete camera;
	
	return 0;
}