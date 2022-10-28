#pragma once

struct aiMesh;

class Model
{
public:
	Model();
	~Model();
	void Load(const char* path);
	void Draw();
	
private:
	unsigned int VAO;
	std::vector <float> vertices;
	std::vector <unsigned int> indexes;

	void GenerateBuffers();
	Model* LoadModel(aiMesh* mesh);


	bool is_root;
	std::vector <Model*> models;
};

