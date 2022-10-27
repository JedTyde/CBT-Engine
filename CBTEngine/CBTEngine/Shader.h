#pragma once

class Shader
{
public:
	void Init(const char* vs, const char* fs);
	void Init();
	void Use();
	void Destroy();
private:
	unsigned int id;
};

