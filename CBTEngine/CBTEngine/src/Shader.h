#pragma once

#include "../vendor/glm/glm/glm.hpp"

class Shader
{
public:
	void Init(const char* vs, const char* fs);
	void Init();
	void InitCam();
	void Use();
	void Destroy();
	void SetModel(glm::mat4 mat);
	void SetView(glm::mat4 mat);
	void SetProj(glm::mat4 mat);
private:
	unsigned int id;
	unsigned int model, proj, view;
};

