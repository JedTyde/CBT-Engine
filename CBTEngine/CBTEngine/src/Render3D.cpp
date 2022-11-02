#include "CBTpch.h"
#include "Render3D.h"
#include "GLFW/glfw3.h"
#include "Input.h"
#include <glad/glad.h>

CBT::Render3D::Render3D()
{
}

CBT::Render3D::~Render3D()
{
}

bool CBT::Render3D::Init()
{
	shader.Init();
	shaderCam.InitCam();
	model.Load("Assets/BakerHouse.fbx");
	cam.SetPerspective(40.0f, 1280/720.0f);
	cam.setPosition(glm::vec3(0,5,10));
	cam.lookAt(glm::vec3(0.0f));
	texture.Load("Assets/bakeHouse.png");

	yaw = -90.0f;
	pitch = 0.0f;

	prevX = CBT::Input::GetMouseX();
	prevY = CBT::Input::GetMouseY();

	firstTime = 0;
	CBT_CORE_INFO("Renderer3D ready");

	return true;
}

void CBT::Render3D::DrawTriangle()
{
	shader.Use();
	triangle.Draw();
}

void CBT::Render3D::DrawModel()
{
	glEnable(GL_DEPTH_TEST);
	shaderCam.Use();
	shaderCam.SetModel(glm::mat4(1.0f));
	shaderCam.SetView(cam.getView());
	shaderCam.SetProj(cam.getProjection());
	texture.Bind(GL_TEXTURE0);
	model.Draw();
}

void CBT::Render3D::Update()
{
	if (CBT::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
	{
		glm::vec3 newPos = cam.getPosition();

		//GOING RIGHT	
		if (CBT::Input::IsKeyPressed(GLFW_KEY_D))
		{
			newPos += glm::normalize(glm::cross(cam.getFront(), cam.getUp())) * 0.5f ;
		}

		//GOING LEFT
		if (CBT::Input::IsKeyPressed(GLFW_KEY_A))
			newPos -= glm::normalize(glm::cross(cam.getFront(), cam.getUp())) * 0.5f;

		//GOING FRONT
		if (CBT::Input::IsKeyPressed(GLFW_KEY_W))
			newPos += cam.getFront() * 0.1f;

		//GOING BACK
		if (CBT::Input::IsKeyPressed(GLFW_KEY_S))
			newPos -= cam.getFront() * 0.1f;

		//GOING UP
		if (CBT::Input::IsKeyPressed(GLFW_KEY_SPACE))
			newPos += cam.getUp();

		//GOING DOWN
		if (CBT::Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
			newPos -= cam.getUp();

		cam.setPosition(newPos);

		//CAMERA ROTATIONS
		float mouseX = CBT::Input::GetMouseX();
		float mouseY = CBT::Input::GetMouseY();

		float offsetX = mouseX - prevX;
		float offsetY = prevY - mouseY;

		if (offsetX != 0) offsetX = offsetX / abs(offsetX);
		if (offsetY != 0) offsetY = offsetY / abs(offsetY);

		yaw += offsetX;
		pitch += offsetY;

		if (pitch > 89.0f) pitch = 89.0f;
		if (pitch < -89.0f) pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		glm::vec3 front = glm::normalize(direction);
		cam.setFront({ front.x, front.y, front.z });
		printf("X%f Y%f Z%f \n", offsetX, offsetY, direction.z);


		prevX = mouseX;
		prevY = mouseY;
	}	

	if (CBT::Input::IsKeyPressed(GLFW_KEY_F))
	{
		glm::vec3 newDirection = { 0, 0, 0 };

		cam.lookAt(newDirection);
	}
}