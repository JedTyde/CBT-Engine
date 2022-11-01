#include "CBTpch.h"
#include "Textures.h"
#include "Render3D.h"

//#include "stb_image.h"
#include "../vendor/stb-master/stb_image.h"
#include <glad/glad.h>

Textures::Textures()
{
}

bool Textures::Load(const std::string& FileName)
{
	m_fileName = FileName;

	stbi_set_flip_vertically_on_load(1);
	int width = 0, height = 0, bpp = 0;
	unsigned char* image_data = stbi_load(m_fileName.c_str(), &width, &height, &bpp, STBI_rgb_alpha);

	if (!image_data)
	{
		printf("Can't load texture from %s - %s\n", m_fileName.c_str(), stbi_failure_reason);
	}
	
	glGenTextures(1, &m_textureObj);
	glBindTexture(GL_TEXTURE_2D, m_textureObj);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image_data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void Textures::Bind(unsigned int TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_textureObj);
}