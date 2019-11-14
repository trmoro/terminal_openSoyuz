#pragma once

#include "core/SType.h"
#pragma message ("type/Model Type is defined")

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "type/Mesh.h"

class Model : public SType
{
public:
	
	//Constructor and Destructor
	Model();
	~Model();

	//Update and Render
	void update() override;
	void render() override;

	//New Model
	static SType* newType(std::vector<std::string> args);

	//Set With String
	void setWithString(std::string str) override;

	//Source https://learnopengl.com/Model-Loading/Model
	void load(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	void processMesh(aiMesh *mesh);

	void clearMesh();

	glm::mat4 getModelRotationMatrix() const;
	glm::mat4 getRotationMatrix() const;

	Mesh* orthoRectInverted() const;

	void setPosition(glm::vec3 pos);
	void setRotation(glm::vec3 rot);
	void setScale(glm::vec3 scale);

	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	glm::vec2 getScale() const;

protected:

	std::vector<Mesh*> m_meshes;
	SVec3* m_position;
	SVec3* m_rotation;
	SVec3* m_scale;
};