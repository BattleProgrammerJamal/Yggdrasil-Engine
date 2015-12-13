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
					m_fov = fov;
					m_aspect = aspect;
					m_near = cnear;
					m_far = cfar;
					updateProj();
				}

				void makeProjOrtho(float width, float height)
				{
					m_type = ORTHOGRAPHIC;
					m_l = 0; m_r = width;
					m_t = 0; m_b = height;
					updateProj();
				}

				void lookAt(const Math::Vector3& eye, const Math::Vector3& target, const Math::Vector3& up)
				{
					m_eye = eye;
					m_target = target;
					m_up = up;
					updateView();
				}

				void updateProj()
				{
					switch (m_type)
					{
						case ORTHOGRAPHIC:
							m_proj = Math::Matrix4::OrthographicMatrix(m_l, m_r, m_t, m_b, 0.0f, 1.0f);
							break;

						case PERSPECTIVE:
							m_proj = Math::Matrix4::PerspectiveMatrix(m_fov, m_aspect, m_near, m_far);
							break;

						default:
							m_proj = Math::Matrix4::PerspectiveMatrix(m_fov, m_aspect, m_near, m_far);
							break;
					}
				}

				void updateView()
				{
					m_view = Math::Matrix4::ViewMatrix(m_eye, m_target, m_up);
				}

				void update()
				{
					updateProj();
					updateView();
				}

				CAMERA_TYPE getCameraType() const { return m_type; }

				Math::Matrix4 getView() const { return m_view; }
				Math::Matrix4 getProj() const { return m_proj; }

			protected:
				CAMERA_TYPE m_type;
				float m_l, m_r, m_t, m_b;
				float m_fov, m_aspect, m_near, m_far;
				Math::Vector3 m_eye, m_target, m_up;
				Math::Matrix4 m_view;
				Math::Matrix4 m_proj;
		};
	};
};

#endif