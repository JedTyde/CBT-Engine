#include "CBTpch.h"
#include "Shader.h"

#include <glad/glad.h>
#include "../vendor/glm/glm/glm.hpp"
#include "../vendor/glm/glm/gtc/type_ptr.hpp"

void Shader::Init(const char* vs, const char* fs)
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
}

void Shader::Init()
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	id = glCreateProgram();
	glAttachShader(id,vertexShader);
	glAttachShader(id,fragmentShader);
	glLinkProgram(id);

	int  success;
	char infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "TUS MUERTOS\n" << infoLog << std::endl; //pendiente de revision
	}
}

void Shader::InitCam()
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 proj;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	int  success;
	char infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "TUS MUERTOS\n" << infoLog << std::endl; //pendiente de revision
	}
	model = glGetUniformLocation(id, "model");
	view = glGetUniformLocation(id, "view");
	proj = glGetUniformLocation(id, "proj");
}

void Shader::Use()
{
	glUseProgram(id);
}

void Shader::Destroy()
{
	glDeleteProgram(id);
}

void Shader::SetModel(glm::mat4 mat)
{
	Use();
	glUniformMatrix4fv(model, 1, GL_FALSE,glm::value_ptr(mat));
}

void Shader::SetView(glm::mat4 mat)
{
	Use();
	glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetProj(glm::mat4 mat)
{
	Use();
	glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(mat));
}

