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
	}

	if (CBT::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
	{
		glm::vec3 newDirection = { 0, 0, 0 };

		cam.lookAt(newDirection);
	}

}