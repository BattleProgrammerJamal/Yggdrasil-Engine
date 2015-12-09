#ifndef YGGDRASIL_MATRIX4_HPP
#define YGGDRASIL_MATRIX4_HPP

#include <iostream>
#include <cmath>

namespace YG
{
	class Matrix4
	{
		public:
			Matrix4()
			{
				identity();
			}

			Matrix4(const Matrix4& u)
			{
				for (unsigned int i = 0; i < 16; ++i)
				{
					m_data[i] = u.m_data[i];
				}
			}

			void identity()
			{
				unsigned int x = 0, y = 0;
				for (unsigned int i = 0; i < 16; ++i)
				{
					x = i / 4, y = i % 4;

					if (x == y)
					{
						m_data[i] = 1.0f;
					}
					else
					{
						m_data[i] = 0.0f;
					}
				}
			}

			float& operator[](unsigned int index)
			{
				return m_data[index];
			}

		private:
			friend std::ostream& operator<<(std::ostream& out, Matrix4& m);
			float m_data[16];
	};
};

#endif