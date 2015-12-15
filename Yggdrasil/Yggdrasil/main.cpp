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

			ygg->getScene()->getByName("Sphere")->transform.Rotate(Math::Vector3(0.0f, dt * 1000.0f, 0.0f));
			ygg->getScene()->getByName("Sphere2")->transform.Rotate(Math::Vector3(dt * 700.0f, dt * 500.0f, 0.0f));

			dt = ygg->getRenderer()->clock.getElapsedTime().asSeconds() - current;
		}
};

int main(int argc, char **argv)
{
	Yggdrasil app(1024, 768, "Yggdrasil Engine 1.0");

	app.getCamera()->eye = Math::Vector3(0.0f, 0.0f, -10.0f);
	
	Core::Material *material = new Core::PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 0.0f, 0.0f), Math::Color(1.0f, 1.0f, 1.0f), 4.0f);
	static_cast<Core::PhongMaterial*>(material)->specularIntensity = 40.0f;
	material->loadTexture("Assets/textures/lava1.jpg");

	Core::Material *material2 = new Core::FresnelMaterial(Math::Color(1.0f, 0.0f, 0.0f), 3.0f, Core::FresnelMaterial::ADDITION);
	material2->loadTexture("Assets/textures/lava1.jpg");

	Core::Mesh *sphere = new Core::Mesh(new Core::SphereGeometry(1.0f, 128, 128), material);
	sphere->setName("Sphere");
	app.addActor(sphere);

	Core::Mesh *sphere2 = new Core::Mesh(new Core::SphereGeometry(1.0f, 128, 128), material2);
	sphere2->setName("Sphere2");
	sphere2->transform.Translate(Math::Vector3(1.0f, 0.0f, 1.0f));
	app.addActor(sphere2);
	
	return app.Run(EventOnRender());
}