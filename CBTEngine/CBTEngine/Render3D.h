#pragma once
#include <CBT/Core.h>
#include <math.h>
#include <CBT/Log.h>

#include "Shader.h"
#include "Triangle.h"


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
	private:
		Triangle triangle;
		Shader shader;
	};
}
