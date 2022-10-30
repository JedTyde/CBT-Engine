#include "Render3D.h"
#include <glad/glad.h>

class Textures
{
public:
	Textures(GLenum TextureTarget, const std::string& FileName);
	bool Load();
	void Bind(GLenum TextureUnit);

private:
	std::string m_fileName;
	GLenum m_textureTarget;
	GLuint m_textureObj;
};