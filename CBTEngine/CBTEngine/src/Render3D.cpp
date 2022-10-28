#include "CBTpch.h"
#include "Render3D.h"

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
	return true;
}

void CBT::Render3D::Drawtriangle()
{
	shader.Use();
	triangle.Draw();
}

void CBT::Render3D::Drawmodel()
{
	shaderCam.Use();
	shaderCam.SetModel(glm::mat4(1.0f));
	shaderCam.SetView(cam.getView());
	shaderCam.SetProj(cam.getProjection());
	model.Draw();
}
