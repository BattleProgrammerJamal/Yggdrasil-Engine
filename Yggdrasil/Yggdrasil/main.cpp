#include "main.hpp"

using namespace std;
using namespace YG;

int main(int argc, char **argv)
{
	Renderer renderer;
	Scene scene;
	Camera camera;

	Actor* actor = 0;

	actor = new Actor("A");
	scene.Add(actor);
	actor = new Actor("B");
	scene.Add(actor);
	actor = new Actor("C");
	scene.Add(actor);
	actor = new Actor("D");
	scene.Add(actor);
	actor = new Actor("E");
	scene.Add(actor);

	while (renderer.render(&scene, &camera)){}

	system("pause");
	return 0;
}