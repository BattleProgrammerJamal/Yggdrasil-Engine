#include "main.hpp"

using namespace std;
using namespace YG;

Core::Mesh *mesh;

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

			mesh->transform.Rotate(Math::Vector3(dt * 10.0f, dt * 40.0f, dt * 20.0f));

			dt = ygg->getRenderer()->clock.getElapsedTime().asSeconds() - current;
		}
};

int main(int argc, char **argv)
{
	Yggdrasil app(1024, 768, "Yggdrasil Engine 1.0");

	app.getCamera()->lookAt(Math::Vector3(0.0f, 0.0f, -10.0f), Math::Vector3(), Math::Vector3(0.0f, 1.0f, 0.0f));
	
	Core::Material *material = new Core::Material("Assets/shaders/lambert.vs", "Assets/shaders/lambert.fs");
	material->loadTexture("Assets/textures/lava2.jpg");
	Core::Geometry *geometry = new Core::SphereGeometry(0.3f, 64, 64);

	mesh = new Core::Mesh(geometry, material);
	mesh->renderStyle = GL_TRIANGLE_STRIP;
	app.addActor(mesh);
	
	return app.Run(EventOnRender());
}