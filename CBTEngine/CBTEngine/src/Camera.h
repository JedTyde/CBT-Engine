#pragma once

#include <CBT/Core.h>

//#include <glm/glm.hpp>
#include "../vendor/glm/glm/glm.hpp"

namespace CBT {
	class CBT_API Camera
	{
	public:
		enum class CameraType {
			INVALID,
			ORTHOGRAPHIC,
			PERSPECTIVE
		};
	private:
		float m_FOV;

		CameraType m_CameraType;

		glm::vec3 m_CameraPos;
		glm::vec3 m_CameraFront;
		glm::vec3 m_CameraUp;

		glm::mat4 m_View;
		glm::mat4 m_Projection;

		float m_NearPlaneDist;
		float m_FarPlaneDist;
		float m_AspectRatio;

		void updateView();
	public:
		Camera();
		~Camera();

		void setPlanes(const float nearPlane, const float farPlane);
		void setAspectRatio(const float aspectRatio);
		float getAspectRatio() { return m_AspectRatio; }

		void setResolution(const int width, const int height);

		void setFOV(const float fov);
		float getFOV() { return m_FOV; }

		void setPosition(glm::vec3 position);
		void setFront(glm::vec3 front);

		glm::vec3 getPosition() { return m_CameraPos; }
		glm::vec3 getFront() { return m_CameraFront; }
		glm::vec3 getUp() { return m_CameraUp; }

		void lookAt(const glm::vec3 position);
		void lookAt(const glm::vec3 cameraPos, const glm::vec3 position, const glm::vec3 camUp);

		void SetPerspective(const float fov, const float aspectRatio, const float nearPlaneDistance = 0.1f, const float farPlaneDistance = 100.0f);
		void SetOrthographic(const int width, const int height, const float nearPlaneDistance = 0.1f, const float farPlaneDistance = 100.0f);

		CameraType GetCameraType() { return m_CameraType; }

		glm::mat4 getView() { return m_View; }
		glm::mat4 getProjection() { return m_Projection; }
	};
}