#include "main.hpp"

using namespace std;
using namespace YG;

int main(int argc, char **argv)
{
	Yggdrasil app(800, 600);
	
	Core::Material mat("Assets/shaders/lambert.vs", "Assets/shaders/lambert.fs");
	mat.loadTexture("Assets/textures/jamal.jpg");

	Core::Actor* actor = new Core::Actor("TestActor");
	//app.addActor(actor);
	
	return app.Run();
}