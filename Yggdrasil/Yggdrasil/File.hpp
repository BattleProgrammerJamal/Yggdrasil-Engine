#ifndef YGGDRASIL_FILE_HPP
#define YGGDRASIL_FILE_HPP

#include "Resource.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

namespace YG
{
	class File : public Resource
	{
		public:
			File(std::string path, char mode = 'r')
				: Resource("FILE")
			{
				m_path = path;
				m_mode = mode;
				Load();
			}

			File(char mode = 'r')
				: Resource("FILE")
			{
				m_path = "";
				m_mode = mode;
			}

			void Load()
			{
				m_loaded = false;
				FILE *f = 0; 
				fopen_s(&f, m_path.c_str(), &m_mode);
				if (f != 0)
				{
					m_content.clear();
					char buff[255];
					while (fgets(buff, 255, f))
					{
						m_content.push_back(std::string(buff));
					}
					m_loaded = true;
				}
			}

			File& Load(const std::string& path)
			{
				setPath(path);
				Load();
				return *this;
			}

			friend std::ostream& operator<<(std::ostream& out, File& file);

			std::string getPath() const { return m_path; }
			void setPath(const std::string& path) { m_path = path; }

			char getMode() const { return m_mode; }
			void setMode(const char mode) { m_mode = mode; }

			bool isLoaded() const { return m_loaded; }

			std::vector<std::string> getContent() const { return m_content; }

			unsigned int size() { return m_content.size(); }

		protected:
			std::vector<std::string> m_content;
			std::string m_path;
			char m_mode;
			bool m_loaded;
	};
};

#endif