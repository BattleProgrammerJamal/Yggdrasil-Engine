#ifndef YGGDRASIL_RENDER_TARGET_HPP
#define YGGDRASIL_RENDER_TARGET_HPP

#include <iostream>
#include "Asset.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace YG
{
	namespace Core
	{
		class RenderTarget : public Asset
		{
			public:
				RenderTarget(GLuint width = 512, GLuint height = 512, GLuint unit = 0, GLuint attachement = 0)
					: Asset("RenderTarget")
				{
					m_width = width;
					m_height = height;
					m_unit = unit;
					m_attachement = attachement;
					m_loaded = false;
					Load();
				}

				void Load()
				{
					m_loaded = false;

					glGenFramebuffers(1, &m_fbo);
					glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

					glGenTextures(1, &m_texture);
					glBindTexture(GL_TEXTURE_2D, m_texture);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_attachement, GL_TEXTURE_2D, m_texture, 0);

					glGenRenderbuffers(1, &m_rbo);
					glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
					glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_width, m_height);

					glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
					
					glBindRenderbuffer(GL_RENDERBUFFER, 0);
					glBindTexture(GL_TEXTURE_2D, 0);
					glBindFramebuffer(GL_FRAMEBUFFER, 0);

					if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
					{
						std::cerr << "Unable to create FrameBufferObject" << std::endl;
						m_loaded = false;
					}
					else
					{
						m_loaded = true;
					}
				}

				void Bind()
				{
					if (m_loaded)
					{
						glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
					}
				}

				void Unbind()
				{
					if (m_loaded)
					{
						glBindFramebuffer(GL_FRAMEBUFFER, 0);
					}
				}

				bool isLoaded() const { return m_loaded; }

				GLuint getUnit() const { return m_unit; }
				void setUnit(GLuint unit) { m_unit = unit; }

				GLuint getWidth() const { return m_width; }
				void setWidth(GLuint width) { m_width = width; }

				GLuint getHeight() const { return m_height; }
				void setHeight(GLuint height) { m_height = height; }

				void setSize(GLuint width, GLuint height) { m_width = width; m_height = height; }

				GLuint getAttachement() const { return m_attachement; }
				void setAttachement(GLuint attachement) { m_attachement = attachement; }

				GLuint getFBO() const { return m_fbo; }

				GLuint getRBO() const { return m_rbo; }

				GLuint getTexture() const { return m_texture; }

			protected:
				bool m_loaded;
				GLuint m_unit;
				GLuint m_width;
				GLuint m_height;
				GLuint m_attachement;
				GLuint m_fbo;
				GLuint m_rbo;
				GLuint m_texture;
		};
	};
};

#endif