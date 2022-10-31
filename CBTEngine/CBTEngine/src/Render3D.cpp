#include "CBTpch.h"
#include "Render3D.h"
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
	cam.lookat(glm::vec3(0.0f));
	texture.Load("Assets/bakeHouse.png");
	return true;
}

void CBT::Render3D::Drawtriangle()
{
	shader.Use();
	triangle.Draw();
}

void CBT::Render3D::Drawmodel()
{
	//glEnable(GL_DEPTH_TEST);
	shaderCam.Use();
	shaderCam.SetModel(glm::mat4(1.0f));
	shaderCam.SetView(cam.getView());
	shaderCam.SetProj(cam.getProjection());
	texture.Bind(GL_TEXTURE0);
	model.Draw();
}
