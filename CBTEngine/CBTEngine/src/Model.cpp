#include "CBTpch.h"
#include "Model.h"
#include <CBT/Log.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>


Model::Model()
{
	is_root = false;
}

Model::~Model()
{
}

void Model::Load(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr)
	{
		is_root = true;
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			models.push_back(LoadModel(scene->mMeshes[i]));
		}
		aiReleaseImport(scene);
	}
	else
		CBT_CORE_ERROR("ERORE LOADING MEHS {0}", path);
	
}

void Model::Draw()
{
	if (is_root)
	{
		for (size_t i = 0; i < models.size(); i++)
		{
			models[i]->Draw();
		}
	}
	else
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, NULL);
	}
}

void Model::GenerateBuffers()
{
	unsigned int VBO;
	unsigned int EBO;

	glGenBuffers(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(int), indexes.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
}

Model* Model::LoadModel(aiMesh* mesh)
{
	Model* model = new Model();
	model->is_root = false;
	for (int j = 0; j < mesh->mNumVertices; j++)
	{
		model->vertices.push_back(mesh->mVertices[j].x);
		model->vertices.push_back(mesh->mVertices[j].y);
		model->vertices.push_back(mesh->mVertices[j].z);

		if (mesh->mTextureCoords[0])
		{
			model->vertices.push_back(mesh->mTextureCoords[0][j].x);
			model->vertices.push_back(mesh->mTextureCoords[0][j].y);
		}
		else {
			model->vertices.push_back(0.0f);
			model->vertices.push_back(0.0f);
		}
	}
	for (int k = 0; k < mesh->mNumFaces; ++k)
	{
		model->indexes.push_back(mesh->mFaces[k].mIndices[0]);
		model->indexes.push_back(mesh->mFaces[k].mIndices[1]);
		model->indexes.push_back(mesh->mFaces[k].mIndices[2]);
	}
	model->GenerateBuffers();
	return model;
}
