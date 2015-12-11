#ifndef YGGDRASIL_RENDER_TARGET_HPP
#define YGGDRASIL_RENDER_TARGET_HPP

#include <iostream>
#include "Texture.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

/*	Version WebGL
var fb=GL.createFramebuffer();
GL.bindFramebuffer(GL.FRAMEBUFFER, fb);

var rb=GL.createRenderbuffer();
GL.bindRenderbuffer(GL.RENDERBUFFER, rb);
GL.renderbufferStorage(GL.RENDERBUFFER, GL.DEPTH_COMPONENT16 , 512, 512);

var texture_rtt=GL.createTexture();
GL.bindTexture(GL.TEXTURE_2D, texture_rtt);
GL.texParameteri(GL.TEXTURE_2D, GL.TEXTURE_MAG_FILTER, GL.LINEAR);
GL.texParameteri(GL.TEXTURE_2D, GL.TEXTURE_MIN_FILTER, GL.LINEAR);
GL.texImage2D(GL.TEXTURE_2D, 0, GL.RGBA, 512, 512, 0, GL.RGBA, GL.UNSIGNED_BYTE, null);

GL.framebufferTexture2D(GL.FRAMEBUFFER, GL.COLOR_ATTACHMENT0, GL.TEXTURE_2D, texture_rtt, 0);

GL.framebufferRenderbuffer(GL.FRAMEBUFFER, GL.DEPTH_ATTACHMENT, GL.RENDERBUFFER, rb);

GL.bindTexture(GL.TEXTURE_2D, null);
GL.bindRenderbuffer(GL.RENDERBUFFER, null);
GL.bindFramebuffer(GL.FRAMEBUFFER, null);
*/

namespace YG
{
	namespace Core
	{
		class RenderTarget
		{
			public:


			protected:

		};
	};
};

#endif