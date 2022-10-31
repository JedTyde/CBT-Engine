#pragma once
#include <CBT/Core.h>
#include <math.h>
#include <CBT/Log.h>

#include "Shader.h"
#include "Triangle.h"
#include "Model.h"
#include "Camera.h"
#include "Textures.h"


namespace CBT {
	class Render3D
	{
	public:
		Render3D();
		~Render3D();

		bool Init();
		void Update();
		void Close();
		void Drawtriangle();
		void Drawmodel();
	private:
		Triangle triangle;
		Model model;
		Shader shader;
		Shader shaderCam;
		Camera cam;
		Textures texture;
	};
}
