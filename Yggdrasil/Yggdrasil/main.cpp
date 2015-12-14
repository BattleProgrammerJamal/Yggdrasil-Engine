#include "main.hpp"

using namespace std;
using namespace YG;

struct EventOnRender : public OnRender
{
	public:
		float current, dt;

		EventOnRender()
		{
			current = 0.0f;
			dt = 0.0f;
		}

		void operator()(Yggdrasil *ygg)
		{
			current = ygg->getRenderer()->clock.getElapsedTime().asSeconds();

			ygg->getScene()->getByName("Sphere")->transform.Rotate(Math::Vector3(0.0f, dt * 40.0f, 0.0f));

			dt = ygg->getRenderer()->clock.getElapsedTime().asSeconds() - current;
		}
};

int main(int argc, char **argv)
{
	Yggdrasil app(1024, 768, "Yggdrasil Engine 1.0");

	app.getCamera()->eye = Math::Vector3(0.0f, -1.0f, -10.0f);
	
	Core::Material *material = new Core::Material("Assets/shaders/lambert.vs", "Assets/shaders/lambert.fs");
	material->loadTexture("Assets/textures/lava1.jpg");

	Core::Material *material2 = new Core::Material("Assets/shaders/lambert.vs", "Assets/shaders/lambert.fs");
	material2->loadTexture("Assets/textures/lava2.jpg").repeat.set(2.0f, 2.0f);

	Core::Mesh *sphere = new Core::Mesh(new Core::SphereGeometry(1.0f, 128, 128), material);
	sphere->setName("Sphere");
	app.addActor(sphere);
	
	return app.Run(EventOnRender());
}