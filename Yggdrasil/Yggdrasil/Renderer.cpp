#include "Renderer.hpp"

using namespace YG;
using namespace Core;

Renderer::Renderer(unsigned int width, unsigned int height, const std::string& title, bool fullscreen)
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

	createDisplay(title, fullscreen);

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
	glDepthFunc(GL_LEQUAL);

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "GPU Version : " << glGetString(GL_RENDERER) << std::endl;

	glViewport(0, 0, m_width, m_height);

	glGenBuffers(1, &m_ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
	glBufferData(GL_UNIFORM_BUFFER, UBO_SIZE(), 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, m_ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);

	fog_enabled = false;
	fog_min_distance = 10.0f;
	fog_max_distance = 100.0f;
	fog_color.set(0.4f, 0.4f, 0.4f);

	m_shadowMap = new RenderTarget(SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
	m_postProcessPass = new RenderTarget(DEFAULT_POST_PROCESS_RT_WIDTH, DEFAULT_POST_PROCESS_RT_HEIGHT);
	m_postProcessShader = new Shader(DEFAULT_POST_PROCESS_VS, DEFAULT_POST_PROCESS_FS);

	GLsizei stride = static_cast<GLsizei>(sizeof(float) * 4);
	std::vector<float> vertice = {
		-1.0f, -1.0f,	0.0f, 0.0f,
		-1.0f, 1.0f,	0.0f, 1.0f,	
		1.0f, -1.0f,	1.0f, 0.0f,
		1.0f, 1.0f,		1.0f, 1.0f
	};
	std::vector<GLuint> indices = { 0, 1, 2, 3 };

	GLuint vbo;
	glGenVertexArrays(1, &m_postProcessVAO);
	glBindVertexArray(m_postProcessVAO);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* vertice.size(), (const void*)&vertice[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(2));

	glBindVertexArray(0);

	glGenBuffers(1, &m_postProcessIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_postProcessIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* indices.size(), (const void*)&indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_postProcessEnabled = false;

	GLsizei stride2 = static_cast<GLsizei>(sizeof(float) * 3);
	std::vector<float> vertice2 = {
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};
	std::vector<GLuint> indices2;
	for (unsigned int i = 0; i < vertice2.size(); ++i){ indices2.push_back(i); }
	
	GLuint vbo2;
	glGenVertexArrays(1, &m_skyboxVAO);
	glBindVertexArray(m_skyboxVAO);
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* vertice2.size(), (const void*)&vertice2[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride2, BUFFER_OFFSET(0));

	glBindVertexArray(0);

	glGenBuffers(1, &m_skyboxIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_skyboxIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* indices2.size(), (const void*)&indices2[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_skyboxEnabled = true;
	std::vector<std::string> paths = {
		DEFAULT_SKYBOX_RIGHT,
		DEFAULT_SKYBOX_LEFT,
		DEFAULT_SKYBOX_TOP,
		DEFAULT_SKYBOX_BOTTOM,
		DEFAULT_SKYBOX_BACK,
		DEFAULT_SKYBOX_FRONT
	};
	m_skyboxCubemap = new Texture(CUBEMAP, paths, 7);
	m_skyboxCubemap->Load();
	m_skyboxShader = new Shader(DEFAULT_SKYBOX_VS, DEFAULT_SKYBOX_FS);
}

Renderer::~Renderer()
{
	for (unsigned int i = 0; i < MAXIMUM_LIGHT; ++i)
	{
		if (m_lights[i])
		{
			delete m_lights[i];
		}
	}

	for (unsigned int i = 0; i < m_keyPressEvents.size(); ++i)
	{
		delete m_keyPressEvents.at(i);
	}
}

void Renderer::createDisplay(const std::string& title, bool fullscreen)
{
	m_fullscreen = fullscreen;

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

GLuint Renderer::bakeShadowMap(Scene *scene, Camera *camera, Light& L, Shader *shadowMapShader)
{
	GLuint shaderID = shadowMapShader->getId();
	m_shadowMap->Bind();
	glUseProgram(shaderID);

	glViewport(0, 0, m_shadowMap->getWidth(), m_shadowMap->getHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

			glm::mat4 shadowMapWorld = mesh->transform.world;
			glm::mat4 shadowMapProj = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
			glm::mat4 shadowMapView = glm::lookAt(glm::vec3(-L.direction.x, -L.direction.y, -L.direction.z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			m_shadowMapWVP = shadowMapProj * shadowMapView * shadowMapWorld;

			glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float)* 16, glm::value_ptr(shadowMapView));
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)* 16, sizeof(float)* 16, glm::value_ptr(shadowMapProj));
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)* 16 + sizeof(float)* 16, sizeof(float)* 16, glm::value_ptr(shadowMapWorld));
			glBindBuffer(GL_UNIFORM_BUFFER, 0);

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

				glUniform3f(lightPosLocation, m_lights[i]->direction.x, m_lights[i]->direction.y, m_lights[i]->direction.z);
				glUniform3f(lightReflLocation, m_lights[i]->reflectance.r, m_lights[i]->reflectance.g, m_lights[i]->reflectance.b);
				glUniform1f(lightIntenLocation, m_lights[i]->intensity);
			}
			GLuint lightCountLocation = glGetUniformLocation(shaderID, "u_lightCount");
			glUniform1i(lightCountLocation, counterLightActive + 1);

			GLuint cameraPositionLocation = glGetUniformLocation(shaderID, "u_cameraPosition");
			glUniform3f(cameraPositionLocation, camera->eye.x, camera->eye.y, camera->eye.z);

			GLuint fogEnabledLocation = glGetUniformLocation(shaderID, "u_fogEnabled");
			if (fog_enabled)
			{
				glUniform1i(fogEnabledLocation, 1);

				GLuint fogMinDistanceLocation = glGetUniformLocation(shaderID, "u_fogMinDistance");
				GLuint fogMaxDistanceLocation = glGetUniformLocation(shaderID, "u_fogMaxDistance");
				GLuint fogColorLocation = glGetUniformLocation(shaderID, "u_fogColor");

				glUniform1f(fogMinDistanceLocation, fog_min_distance);
				glUniform1f(fogMaxDistanceLocation, fog_max_distance);
				glUniform3f(fogColorLocation, fog_color.r, fog_color.g, fog_color.b);
			}
			else
			{
				glUniform1i(fogEnabledLocation, 0);
			}

			glUniform1f(glGetUniformLocation(shaderID, "time"), (float)clock.getElapsedTime().asMilliseconds());
			glUniform2i(glGetUniformLocation(shaderID, "u_iScreenSize"), (int)(1.0f / m_width), (int)(1.0f / m_height));

			glBindVertexArray(geo->getVAO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geo->getIBO());

			glDrawElements(mesh->renderStyle, geo->getIndices().size(), GL_UNSIGNED_INT, (const void*)0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
	}
	
	glUseProgram(0);
	m_shadowMap->Unbind();

	return m_shadowMap->getTexture();
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

		if (m_event.type == sf::Event::KeyPressed)
		{
			for (OnKeyPress *evt : m_keyPressEvents)
			{
				(*evt)(m_event.key.code);
			}
		}
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	GLuint shadowMap;
	for (unsigned int i = 0; i < 16; ++i)
	{
		if (m_lights[i] == 0){ continue; }
		if (m_lights[i]->isCastShadow() == false) { continue; }

		shadowMap = bakeShadowMap(scene, camera, *m_lights[i]);
	}
	glDisable(GL_BLEND);

	if (m_postProcessEnabled)
	{ 
		m_postProcessPass->Bind(); 
		glViewport(0, 0, m_postProcessPass->getWidth(), m_postProcessPass->getHeight());
	}
	else
	{
		if (!m_fullscreen)
		{
			sf::Vector2u windowSize = m_window->getSize();
			glViewport(0, 0, windowSize.x, windowSize.y);
		}
		else
		{
			glViewport(0, 0, m_width, m_height);
		}
	}
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if (m_skyboxEnabled)
	{
		glDepthMask(GL_FALSE);
		m_skyboxShader->Bind();
		glActiveTexture(GL_TEXTURE0 + 7);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyboxCubemap->getTextureId());
		GLuint skyboxLocation = glGetUniformLocation(m_skyboxShader->getId(), "u_skybox");
		glUniform1i(skyboxLocation, 7);

		glBindVertexArray(m_skyboxVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_skyboxIBO);
		
		glm::mat4 world = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(glm::mat3(camera->view));

		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float)* 16, glm::value_ptr(view));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)* 16, sizeof(float)* 16, glm::value_ptr(camera->proj));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)* 16 + sizeof(float)* 16, sizeof(float)* 16, glm::value_ptr(world));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glUniform1f(glGetUniformLocation(m_skyboxShader->getId(), "time"), (float)clock.getElapsedTime().asMilliseconds());

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (const void*)0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		m_skyboxShader->Unbind();
		glDepthMask(GL_TRUE);
	}

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

			glm::mat4 biasMatrix(
				0.5, 0.0, 0.0, 0.0,
				0.0, 0.5, 0.0, 0.0,
				0.0, 0.0, 0.5, 0.0,
				0.5, 0.5, 0.5, 1.0);
			glm::mat4 depthBiasWVP = biasMatrix * m_shadowMapWVP;

			glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_depthBiasWVP"), 1, GL_FALSE, glm::value_ptr(depthBiasWVP));

			glActiveTexture(GL_TEXTURE0 + 9);
			glBindTexture(GL_TEXTURE_2D, shadowMap);
			GLuint shadowMapLocation = glGetUniformLocation(shaderID, "u_shadowMap");
			glUniform1i(shadowMapLocation, 9);

			glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float)* 16, glm::value_ptr(camera->view));
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)* 16, sizeof(float)* 16, glm::value_ptr(camera->proj));
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)* 16 + sizeof(float)* 16, sizeof(float)* 16, glm::value_ptr(mesh->transform.world));
			glBindBuffer(GL_UNIFORM_BUFFER, 0);

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

				glUniform3f(lightPosLocation, m_lights[i]->direction.x, m_lights[i]->direction.y, m_lights[i]->direction.z);
				glUniform3f(lightReflLocation, m_lights[i]->reflectance.r, m_lights[i]->reflectance.g, m_lights[i]->reflectance.b);
				glUniform1f(lightIntenLocation, m_lights[i]->intensity);
			}
			GLuint lightCountLocation = glGetUniformLocation(shaderID, "u_lightCount");
			glUniform1i(lightCountLocation, counterLightActive + 1);

			GLuint cameraPositionLocation = glGetUniformLocation(shaderID, "u_cameraPosition");
			glUniform3f(cameraPositionLocation, camera->eye.x, camera->eye.y, camera->eye.z);

			GLuint fogEnabledLocation = glGetUniformLocation(shaderID, "u_fogEnabled");
			if (fog_enabled)
			{
				glUniform1i(fogEnabledLocation, 1);

				GLuint fogMinDistanceLocation = glGetUniformLocation(shaderID, "u_fogMinDistance");
				GLuint fogMaxDistanceLocation = glGetUniformLocation(shaderID, "u_fogMaxDistance");
				GLuint fogColorLocation = glGetUniformLocation(shaderID, "u_fogColor");

				glUniform1f(fogMinDistanceLocation, fog_min_distance);
				glUniform1f(fogMaxDistanceLocation, fog_max_distance);
				glUniform3f(fogColorLocation, fog_color.r, fog_color.g, fog_color.b);
			}
			else
			{
				glUniform1i(fogEnabledLocation, 0);
			}

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
	if (m_postProcessEnabled)
	{
		m_postProcessPass->Unbind();

		glViewport(0, 0, m_width, m_height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		m_postProcessShader->Bind();
		glBindVertexArray(m_postProcessVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_postProcessIBO);

		glActiveTexture(GL_TEXTURE0 + 14);
		glBindTexture(GL_TEXTURE_2D, m_postProcessPass->getTexture());
		GLuint screenTextureLocation = glGetUniformLocation(m_postProcessShader->getId(), "u_sceneTexture");
		glUniform1i(screenTextureLocation, 14);

		glUniform1f(glGetUniformLocation(m_postProcessShader->getId(), "time"), (float)clock.getElapsedTime().asMilliseconds());

		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (const void*)0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		m_postProcessShader->Unbind();
	}

	m_window->display();

	deltaTime = (static_cast<float>(clock.getElapsedTime().asMilliseconds()) - beginTime) / 1000.0f;
	return true;
}