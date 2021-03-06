#ifndef YGGDRASIL_MATRIX4_HPP
#define YGGDRASIL_MATRIX4_HPP

#include <iostream>
#include <cmath>
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Math.hpp"

namespace YG
{
	namespace Math
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

				Matrix4& transpose()
				{
					float temp = 0.0f;
					temp = m_data[4];
					m_data[4] = m_data[1];
					m_data[1] = temp;

					temp = m_data[8];
					m_data[8] = m_data[2];
					m_data[2] = temp;

					temp = m_data[13];
					m_data[13] = m_data[7];
					m_data[7] = temp;

					temp = m_data[14];
					m_data[14] = m_data[11];
					m_data[11] = temp;
					return *this;
				}

				float& operator[](unsigned int index)
				{
					return m_data[index];
				}

				Matrix4 operator+(const Matrix4& m)
				{
					Matrix4 rslt;
					for (unsigned int i = 0; i < 16; ++i)
					{
						rslt[i] = m_data[i] + m.m_data[i];
					}
					return rslt;
				}

				Matrix4& operator+=(const Matrix4& m)
				{
					*this = operator+(m);
					return *this;
				}

				Matrix4 operator-(const Matrix4& m)
				{
					Matrix4 rslt;
					for (unsigned int i = 0; i < 16; ++i)
					{
						rslt[i] = m_data[i] - m.m_data[i];
					}
					return rslt;
				}

				Matrix4& operator-=(const Matrix4& m)
				{
					*this = operator-(m);
					return *this;
				}

				Matrix4 operator*(const Matrix4& m)
				{
					Matrix4 rslt;
					/*
					rslt[0] =	m_data[0] * m.m_data[0] + m_data[1] * m.m_data[4] + m_data[2] * m.m_data[8] + m_data[3] * m.m_data[12];
					rslt[1] =	m_data[0] * m.m_data[1] + m_data[1] * m.m_data[5] + m_data[2] * m.m_data[9] + m_data[3] * m.m_data[13];
					rslt[2] =	m_data[0] * m.m_data[2] + m_data[1] * m.m_data[6] + m_data[2] * m.m_data[10] + m_data[3] * m.m_data[14];
					rslt[3] =	m_data[0] * m.m_data[3] + m_data[1] * m.m_data[7] + m_data[2] * m.m_data[11] + m_data[3] * m.m_data[15];
					
					rslt[4] =	m_data[4] * m.m_data[0] + m_data[5] * m.m_data[4] + m_data[6] * m.m_data[8] + m_data[7] * m.m_data[12];
					rslt[5] =	m_data[4] * m.m_data[1] + m_data[5] * m.m_data[5] + m_data[6] * m.m_data[9] + m_data[7] * m.m_data[13];
					rslt[6] =	m_data[4] * m.m_data[2] + m_data[5] * m.m_data[6] + m_data[6] * m.m_data[10] + m_data[7] * m.m_data[14];
					rslt[7] =	m_data[4] * m.m_data[3] + m_data[5] * m.m_data[7] + m_data[6] * m.m_data[11] + m_data[7] * m.m_data[15];
					
					rslt[8] =	m_data[8] * m.m_data[0] + m_data[9] * m.m_data[4] + m_data[10] * m.m_data[8] + m_data[11] * m.m_data[12];
					rslt[9] =	m_data[8] * m.m_data[1] + m_data[9] * m.m_data[5] + m_data[10] * m.m_data[9] + m_data[11] * m.m_data[13];
					rslt[10] =	m_data[8] * m.m_data[2] + m_data[9] * m.m_data[6] + m_data[10] * m.m_data[10] + m_data[11] * m.m_data[14];
					rslt[11] =	m_data[8] * m.m_data[3] + m_data[9] * m.m_data[7] + m_data[10] * m.m_data[11] + m_data[11] * m.m_data[15];
					
					rslt[12] =	m_data[12] * m.m_data[0] + m_data[13] * m.m_data[4] + m_data[14] * m.m_data[8] + m_data[15] * m.m_data[12];
					rslt[13] =	m_data[12] * m.m_data[1] + m_data[13] * m.m_data[5] + m_data[14] * m.m_data[9] + m_data[15] * m.m_data[13];
					rslt[14] =	m_data[12] * m.m_data[2] + m_data[13] * m.m_data[6] + m_data[14] * m.m_data[10] + m_data[15] * m.m_data[14];
					rslt[15] =	m_data[12] * m.m_data[3] + m_data[13] * m.m_data[7] + m_data[14] * m.m_data[11] + m_data[15] * m.m_data[15];
					*/
					for (unsigned int i = 0; i < 4; ++i)
					{
						for (unsigned int j = 0; j < 4; ++j)
						{
							unsigned int index = j + i * 4;

							float sum = 0.0f;
							for (unsigned int k = 0; k < 4; ++k)
							{
								unsigned int index1 = i + k * 4;
								unsigned int index2 = j + k * 4;
								sum = sum + (m_data[index] * m.m_data[index2]);
							}

							rslt[index] = sum;
						}
					}
					
					return rslt;
				}
			
				Matrix4& operator*=(const Matrix4& m)
				{
					*this = operator*(m);
					return *this;
				}
				
				/*
				void fromQuaternion(const Quaternion& q)
				{
					m_data[0] = 1.0f - 2.0f * (q.y * q.y);
					m_data[1] = 2.0f * q.x * q.y - 2.0f * q.z * q.w;
					m_data[2] = 2.0f * q.x * q.z + 2.0f * q.y * q.w;

					m_data[4] = 2.0f * q.x * q.y + 2.0f * q.z * q.w;
					m_data[5] = 1.0f - 2.0f * (q.x * q.x) - 2.0f * (q.z * q.z);
					m_data[6] = 2.0f * q.y * q.z - 2.0f * q.x * q.w;

					m_data[8] = 2.0f * q.x * q.z - 2.0f * q.y * q.w;
					m_data[9] = 2.0f * q.y * q.z + 2.0f * q.x * q.w;
					m_data[10] = 1.0f - 2.0f * (q.x * q.x) - 2.0f * (q.y * q.y);
				}
				*/
				
				static Matrix4 TranslationMatrix(const Vector3& v)
				{
					Matrix4 mat;
					mat[3] = v.x;
					mat[7] = v.y;
					mat[11] = v.z;
					return mat;
				}

				static Matrix4 RotationEulerXMatrix(float angle)
				{
					Matrix4 mat;
					mat[5] = cos(angle);
					mat[6] = -sin(angle);
					mat[9] = sin(angle);
					mat[10] = cos(angle);
					return mat;
				}

				static Matrix4 RotationEulerYMatrix(float angle)
				{
					Matrix4 mat;
					mat[0] = cos(angle);
					mat[8] = -sin(angle);
					mat[2] = sin(angle);
					mat[10] = cos(angle);
					return mat;
				}

				static Matrix4 RotationEulerZMatrix(float angle)
				{
					Matrix4 mat;
					mat[0] = cos(angle);
					mat[4] = -sin(angle);
					mat[1] = sin(angle);
					mat[5] = cos(angle);
					return mat;
				}

				static Matrix4 RotationEulerMatrix(const Vector3& v)
				{
					Matrix4 rotX = RotationEulerXMatrix(v.x);
					Matrix4 rotY = RotationEulerYMatrix(v.y);
					Matrix4 rotZ = RotationEulerZMatrix(v.z);
					return rotZ * rotY * rotX;
				}

				static Matrix4 ScaleMatrix(const Vector3& v)
				{
					Matrix4 mat;
					mat[0] = v.x;
					mat[5] = v.y;
					mat[10] = v.z;
					return mat;
				}

				static Matrix4 OrthographicMatrix(float l, float r, float t, float b, float cnear, float cfar)
				{
					Matrix4 mat;
					mat[0] = 2.0f / (r - l);
					mat[3] = -((r + l) / (r - l));
					mat[5] = 2.0f / (t - b);
					mat[7] = -((t + b) / (t - b));
					mat[10] = -2.0f / (cfar - cnear);
					mat[11] = -(cfar + cnear) / (cfar - cnear);
					return mat;
				}

				static Matrix4 PerspectiveMatrix(float fov, float aspect, float cnear, float cfar)
				{
					float zRange = cnear - cfar;
					float tanHalfFov = tanf(Math::Rad(fov / 2.0f));
					Matrix4 mat;
					mat[0] = 1.0f / (tanHalfFov * aspect);
					mat[5] = 1.0f / tanHalfFov;
					mat[10] = (-cnear - cfar) / zRange;
					mat[14] = 2.0f * cfar * cnear / zRange;
					return mat;
				}

				static Matrix4 ViewMatrix(Vector3& eye, Vector3& target, Vector3& up)
				{
					Matrix4 orientation;
					Vector3 zaxis = (eye - target).normalize();
					Vector3 xaxis = up.cross(zaxis).normalize();
					Vector3 yaxis = zaxis.cross(xaxis);
					orientation[0] = xaxis.x;
					orientation[1] = yaxis.x;
					orientation[2] = zaxis.x;
					orientation[4] = xaxis.y;
					orientation[5] = yaxis.y;
					orientation[6] = zaxis.y;
					orientation[8] = xaxis.z;
					orientation[9] = yaxis.z;
					orientation[10] = zaxis.z;
					Matrix4 translation = TranslationMatrix(-eye);
					Matrix4 view = orientation * translation;

					return view;
				}

				const float* getData() const { return m_data; }

			private:
				friend std::ostream& operator<<(std::ostream& out, Matrix4& m);
				float m_data[16];
		};
	};
};

#endif