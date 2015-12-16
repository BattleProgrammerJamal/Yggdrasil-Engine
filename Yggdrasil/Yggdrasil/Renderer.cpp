#include "Renderer.hpp"

using namespace YG;
using namespace Core;

Renderer::Renderer(unsigned int width, unsigned int height, const std::string& title)
{
	m_width = width;
	m_height = height;
	m_fullscreen = false;
	m_clearColor = Math::Color(0.0f, 0.0f, 0.0f, 1.0f);
	m_currentLightIndex = 0;
	for (unsigned int i = 0; i < MAXIMUM_LIGHT; ++i)
	{
		m_lights[i] = 0;
	}

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

	shadowMap = new RenderTarget(512, 512, 0, {  GL_COLOR_ATTACHMENT0 });
	shadowMapShader = new Shader("Assets/shaders/shadowMap.vs", "Assets/shaders/shadowMap.fs");
}

Renderer::~Renderer()
{
	delete shadowMap;
	for (unsigned int i = 0; i < MAXIMUM_LIGHT; ++i)
	{
		if (m_lights[i])
		{
			delete m_lights[i];
		}
	}
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
	static float beginTime = 0.0f;
	beginTime = static_cast<float>(clock.getElapsedTime().asMilliseconds());
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

	// SHADOW MAP PASS

	//glDepthMask(GL_FALSE);
	//glDepthFunc(GL_LEQUAL);

	unsigned int shadowMapLightIndex = 0;
	shadowMap->Bind();
	glViewport(0, 0, shadowMap->getWidth(), shadowMap->getHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	for (Actor* actor : scene->getChildren())
	{
		actor->transform.updateWorldMatrix();
		Mesh *mesh = static_cast<Mesh*>(actor);
		Geometry *geo = mesh->getGeometry();
		Material *mat = mesh->getMaterial();
		if (geo == 0 || mat == 0) { continue; }
		GLuint shaderID = mat->getShader();

		shadowMapShader->Bind();
		glActiveTexture(GL_TEXTURE0 + 14);
		glBindTexture(GL_TEXTURE_2D, shadowMap->getTexture());
		GLuint shadowMapLocation = glGetUniformLocation(shaderID, "u_shadowMap");
		glUniform1i(shadowMapLocation, shadowMap->getTexture());

		glm::mat4 lightProj = glm::ortho(0, (int)shadowMap->getWidth(), (int)shadowMap->getHeight(), 0);
		glm::mat4 lightView = glm::lookAt(glm::vec3(m_lights[shadowMapLightIndex]->position.x, m_lights[shadowMapLightIndex]->position.y, m_lights[shadowMapLightIndex]->position.z), glm::vec3(actor->transform.position.x, actor->transform.position.y, actor->transform.position.z), glm::vec3(0.0f, 1.0f, 0.0f));

		if (UBO_SUPPORTED == false)
		{
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_world"), 1, GL_FALSE, glm::value_ptr(mesh->transform.world));
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_view"), 1, GL_FALSE, glm::value_ptr(lightView));
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_proj"), 1, GL_FALSE, glm::value_ptr(lightProj));
		}
		else
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float)* 16, glm::value_ptr(lightView));
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)* 16, sizeof(float)* 16, glm::value_ptr(lightProj));
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)* 16 + sizeof(float)* 16, sizeof(float)* 16, glm::value_ptr(mesh->transform.world));
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		unsigned int counterLightActive = 0;
		for (unsigned int i = 0; i < MAXIMUM_LIGHT; ++i)
		{
			if (m_lights[i]) { counterLightActive = (i == 0) ? counterLightActive : (counterLightActive + 1); }
			else { continue; }

			std::stringstream stream1, stream2, stream3;
			stream1 << "u_lights[" << counterLightActive << "].position";
			stream2 << "u_lights[" << counterLightActive << "].reflectance";
			stream3 << "u_lights[" << counterLightActive << "].intensity";
			GLuint lightPosLocation = glGetUniformLocation(shaderID, stream1.str().c_str());
			GLuint lightReflLocation = glGetUniformLocation(shaderID, stream2.str().c_str());
			GLuint lightIntenLocation = glGetUniformLocation(shaderID, stream3.str().c_str());

			glUniform3f(lightPosLocation, m_lights[i]->position.x, m_lights[i]->position.y, m_lights[i]->position.z);
			glUniform3f(lightReflLocation, m_lights[i]->reflectance.r, m_lights[i]->reflectance.g, m_lights[i]->reflectance.b);
			glUniform1f(lightIntenLocation, m_lights[i]->intensity);
		}
		GLuint lightCountLocation = glGetUniformLocation(shaderID, "u_lightCount");
		glUniform1i(lightCountLocation, counterLightActive);

		glUniform1f(glGetUniformLocation(shaderID, "time"), (float)clock.getElapsedTime().asMilliseconds());
		glUniform2i(glGetUniformLocation(shaderID, "u_iScreenSize"), (int)(1.0f / m_width), (int)(1.0f / m_height));

		glBindVertexArray(geo->getVAO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geo->getIBO());
		
		glDrawElements(mesh->renderStyle, geo->getIndices().size(), GL_UNSIGNED_INT, (const void*)0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	shadowMapShader->Unbind();
	shadowMap->Unbind();

	// RENDER PASS

	//glDepthMask(GL_TRUE);
	//glDepthFunc(GL_LESS);

	glViewport(0, 0, m_width, m_height);
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	for (Actor* actor : scene->getChildren())
	{
		actor->transform.updateWorldMatrix();
		if (typeid(Mesh) == typeid(*actor))
		{
			Mesh *mesh = static_cast<Mesh*>(actor);
			Geometry *geo = mesh->getGeometry();
			Material *mat = mesh->getMaterial();
			if (geo == 0 || mat == 0) { continue; }
			GLuint shaderID = mat->getShader();

			mat->Bind();
			glActiveTexture(GL_TEXTURE0 + 14);
			glBindTexture(GL_TEXTURE_2D, shadowMap->getTexture());
			GLuint shadowMapLocation = glGetUniformLocation(shaderID, "u_shadowMap");
			glUniform1i(shadowMapLocation, shadowMap->getTexture());

			if (UBO_SUPPORTED == false)
			{
				glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_world"), 1, GL_FALSE, glm::value_ptr(mesh->transform.world));
				glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_view"), 1, GL_FALSE, glm::value_ptr(camera->view));
				glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_proj"), 1, GL_FALSE, glm::value_ptr(camera->proj));
			}
			else
			{
				glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
				glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float)* 16, glm::value_ptr(camera->view));
				glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)* 16, sizeof(float)* 16, glm::value_ptr(camera->proj));
				glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)* 16 + sizeof(float)* 16, sizeof(float)* 16, glm::value_ptr(mesh->transform.world));
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}

			unsigned int counterLightActive = 0;
			for (unsigned int i = 0; i < MAXIMUM_LIGHT; ++i)
			{
				if (m_lights[i]) { counterLightActive = (i == 0) ? counterLightActive : (counterLightActive + 1); } else { continue; }

				std::stringstream stream1, stream2, stream3;
				stream1 << "u_lights[" << counterLightActive << "].position";
				stream2 << "u_lights[" << counterLightActive << "].reflectance";
				stream3 << "u_lights[" << counterLightActive << "].intensity";
				GLuint lightPosLocation = glGetUniformLocation(shaderID, stream1.str().c_str());
				GLuint lightReflLocation = glGetUniformLocation(shaderID, stream2.str().c_str());
				GLuint lightIntenLocation = glGetUniformLocation(shaderID, stream3.str().c_str());

				glUniform3f(lightPosLocation, m_lights[i]->position.x, m_lights[i]->position.y, m_lights[i]->position.z);
				glUniform3f(lightReflLocation, m_lights[i]->reflectance.r, m_lights[i]->reflectance.g, m_lights[i]->reflectance.b);
				glUniform1f(lightIntenLocation, m_lights[i]->intensity);
			}
			GLuint lightCountLocation = glGetUniformLocation(shaderID, "u_lightCount");
			glUniform1i(lightCountLocation, counterLightActive);

			glUniform1f(glGetUniformLocation(shaderID, "time"), (float)clock.getElapsedTime().asMilliseconds());
			glUniform2i(glGetUniformLocation(shaderID, "u_iScreenSize"), (int)(1.0f / m_width), (int)(1.0f / m_height));

			glBindVertexArray(geo->getVAO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geo->getIBO());

			glDrawElements(mesh->renderStyle, geo->getIndices().size(), GL_UNSIGNED_INT, (const void*)0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
			mat->Unbind();
		}
	}

	m_window->display();

	deltaTime = (static_cast<float>(clock.getElapsedTime().asMilliseconds()) - beginTime) / 1000.0f;
	return true;
}