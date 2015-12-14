#ifndef YGGDRASIL_CAMERA_HPP
#define YGGDRASIL_CAMERA_HPP

#include <iostream>
#include "Matrix4.hpp"

namespace YG
{
	namespace Core
	{
		enum CAMERA_TYPE
		{
			ORTHOGRAPHIC,
			PERSPECTIVE
		};

		class Camera
		{
			public:
				float l, r, t, b;
				float fov, aspect, cnear, cfar;
				Math::Vector3 eye, target, up;
				Math::Matrix4 view;
				Math::Matrix4 proj;

				Camera(float fov, float aspect, float cnear, float cfar)
				{
					m_type = PERSPECTIVE;
					makeProjPerspective(fov, aspect, cnear, cfar);
					lookAt(Math::Vector3(), Math::Vector3(), Math::Vector3(0.0f, 1.0f, 0.0f));
				}

				Camera(float width, float height)
				{
					m_type = ORTHOGRAPHIC;
					makeProjOrtho(width, height);
					lookAt(Math::Vector3(), Math::Vector3(), Math::Vector3(0.0f, 1.0f, 0.0f));
					update();
				}

				~Camera()
				{
				}

				void makeProjPerspective(float fov, float aspect, float cnear, float cfar)
				{
					m_type = PERSPECTIVE;
					this->fov = fov;
					this->aspect = aspect;
					this->cnear = cnear;
					this->cfar = cfar;
					updateProj();
				}

				void makeProjOrtho(float width, float height)
				{
					m_type = ORTHOGRAPHIC;
					this->l = 0; this->r = width;
					this->t = 0; this->b = height;
					updateProj();
				}

				void lookAt(const Math::Vector3& eye, const Math::Vector3& target, const Math::Vector3& up)
				{
					this->eye = eye;
					this->target = target;
					this->up = up;
					updateView();
				}

				void updateProj()
				{
					switch (m_type)
					{
						case ORTHOGRAPHIC:
							proj = Math::Matrix4::OrthographicMatrix(l, r, t, b, 0.0f, 1.0f);
							break;

						case PERSPECTIVE:
							proj = Math::Matrix4::PerspectiveMatrix(fov, aspect, cnear, cfar);
							break;

						default:
							proj = Math::Matrix4::PerspectiveMatrix(fov, aspect, cnear, cfar);
							break;
					}
				}

				void updateView()
				{
					view = Math::Matrix4::ViewMatrix(eye, target, up);
				}

				void update()
				{
					updateProj();
					updateView();
				}

				CAMERA_TYPE getCameraType() const { return m_type; }

			protected:
				CAMERA_TYPE m_type;
		};
	};
};

#endif