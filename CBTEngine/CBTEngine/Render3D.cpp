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
	return true;
}

void CBT::Render3D::Drawtriangle()
{
	shader.Use();
	triangle.Draw();
}
