#include "Renderer.hpp"

using namespace YG;
using namespace Core;

Renderer::Renderer(unsigned int width, unsigned int height, const std::string& title)
{
	m_width = width;
	m_height = height;
	m_fullscreen = false;
	m_clearColor = Math::Color(0.0f, 0.0f, 0.0f, 1.0f);

	createDisplay(title);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
	}

	GLint numExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
	int index = 0;
	for (index = 0; index < numExtensions; ++index)
	{
		glGetStringi(GL_EXTENSIONS, index);
	}

	glEnable(GL_DEPTH_TEST);

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "GPU Version : " << glGetString(GL_RENDERER) << std::endl;

	glViewport(0, 0, m_width, m_height);

	glGenBuffers(1, &m_ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
	glBufferData(GL_UNIFORM_BUFFER, UBO_SIZE(), 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, m_ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
}

Renderer::~Renderer()
{
}

void Renderer::createDisplay(const std::string& title)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = OPENGL_MAJOR_VERSION;
	settings.minorVersion = OPENGL_MINOR_VERSION;

	if (!m_fullscreen)
	{
		m_window = new sf::Window(sf::VideoMode(m_width, m_height), title.c_str(), sf::Style::Default, settings);
	}
	else
	{
		m_window = new sf::Window(sf::VideoMode(), title.c_str(), sf::Style::Fullscreen, settings);
	}
}

bool Renderer::render(Scene *scene, Camera *camera)
{
	camera->updateView();

	if (m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed || (m_event.type == sf::Event::KeyPressed && m_event.key.code == sf::Keyboard::Escape))
		{
			return false;
		}

		if (m_event.type == sf::Event::Resized)
		{
			sf::Vector2u windowSize = m_window->getSize();
			m_width = windowSize.x;
			m_height = windowSize.y;
			glViewport(0, 0, m_width, m_height);
		}
	}

	glViewport(0, 0, m_width, m_height);
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	for (Actor* actor : scene->getChildren())
	{
		if (typeid(Mesh) == typeid(*actor))
		{
			Mesh *mesh = static_cast<Mesh*>(actor);
			Geometry *geo = mesh->getGeometry();
			Material *mat = mesh->getMaterial();
			if (geo == 0 || mat == 0) { continue; }
			GLuint shaderID = mat->getShader();

			mat->Bind();

			glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float) * 16, camera->view.getData());
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float) * 16, sizeof(float) * 16, camera->proj.getData());
			glBindBuffer(GL_UNIFORM_BUFFER, 0);

			Math::Matrix4 T = Math::Matrix4::TranslationMatrix(mesh->transform.position);
			Math::Matrix4 Rx = Math::Matrix4::RotationEulerXMatrix(mesh->transform.rotation.x);
			Math::Matrix4 Ry = Math::Matrix4::RotationEulerXMatrix(mesh->transform.rotation.y);
			Math::Matrix4 Rz = Math::Matrix4::RotationEulerXMatrix(mesh->transform.rotation.z);
			Math::Matrix4 S = Math::Matrix4::ScaleMatrix(mesh->transform.scale);
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_translation"), 1, GL_TRUE, T.getData());
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_rotationX"), 1, GL_TRUE, Rx.getData());
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_rotationY"), 1, GL_TRUE, Ry.getData());
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_rotationZ"), 1, GL_TRUE, Rz.getData());
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_scale"), 1, GL_TRUE, S.getData());
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_world"), 1, GL_TRUE, mesh->transform.world.getData());

			glUniform1f(glGetUniformLocation(shaderID, "time"), (float)clock.getElapsedTime().asMilliseconds());

			glUniform2i(glGetUniformLocation(shaderID, "u_iScreenSize"), (int)(1.0f / m_width), (int)(1.0f / m_height));

			glBindVertexArray(geo->getVAO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geo->getIBO());

			glDrawElements(mesh->renderStyle, geo->getIndices().size(), GL_UNSIGNED_INT, (const void*)0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			mat->Unbind();
		}
	}

	m_window->display();
	return true;
}