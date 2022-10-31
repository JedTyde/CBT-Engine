#pragma once

class Textures
{
public:
	Textures();
	bool Load(const std::string& FileName);
	void Bind(unsigned int TextureUnit);

private:
	std::string m_fileName;
	unsigned int m_textureObj;
};