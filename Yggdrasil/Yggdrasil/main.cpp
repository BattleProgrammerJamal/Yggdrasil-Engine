#include "main.hpp"

using namespace std;
using namespace YG;

int main(int argc, char **argv)
{
	Core::Renderer renderer(1024, 768, "ESGI \\ Jamal BOUIZEM - OpenGL Renderer");
	Core::Scene scene;
	Core::Camera camera;

	Core::Actor* actor = new Core::Actor("TestActor");
	//scene.Add(actor);

	while (renderer.render(&scene, &camera)){}
	return 0;
}