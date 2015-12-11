#ifndef YGGDRASIL_IMAGE_HPP
#define YGGDRASIL_IMAGE_HPP

#include <iostream>
#include <fstream>
#include "Resource.hpp"
#include "STB/stb_image.h"

namespace YG
{
	namespace Core
	{
		class Image : public Resource
		{
			public:
				Image(std::string path)
					: Resource("IMAGE")
				{
					m_path = path;
					m_loaded = false;
					Load();
				}

				void Load()
				{
					m_loaded = false;

					m_data = stbi_load(m_path.c_str(), &m_width, &m_height, &m_comp, 0);

					m_loaded = true;
				}

				bool isLoaded() const { return m_loaded; }

				std::string getPath() const { return m_path; }
				void setPath(const std::string& path) { m_path = path; }

				unsigned char* getData() const { return m_data; }

				int getWidth() const { return m_width; }
				int getHeight() const { return m_height; }
				int getComp() const { return m_comp; }

			protected:
				bool m_loaded;
				std::string m_path;
				unsigned char* m_data;
				int m_width;
				int m_height;
				int m_comp;
		};
	};
};

#endif