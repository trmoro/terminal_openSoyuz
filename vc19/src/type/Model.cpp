#include "type/Model.h"

#include "core/Root.h"

//Create
Model::Model()
{
	m_meshes = std::vector<Mesh*>();

	m_position	= new SVec3(glm::vec3(0, 0, 0) );
	m_rotation	= new SVec3(glm::vec3(0, 0, 0) );
	m_scale		= new SVec3(glm::vec3(1, 1, 1) );

	m_position->name = "position";
	m_position->setParent(this);

	m_rotation->name = "rotation";
	m_rotation->setParent(this);

	m_scale->name = "scale";
	m_scale->setParent(this);
}

//Delete
Model::~Model()
{
	clearMesh();
}

//New Type
SType* Model::newType(std::vector<std::string> args)
{
	//New
	Model* st = new Model();
	st->name = "unnamed_model";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Load
	if (args.size() > 2)
		st->setWithString(args[2]);

	//Return
	return st;
}

//Set With String
void Model::setWithString(std::string str)
{
	//Split
	std::string ns = searchToString(str, Root::getInstance()->getCurrentObject());

	//Load
	load(str);
}

//Update
void Model::update()
{

}

//Render
void Model::render()
{
	for (Mesh* m : m_meshes)
		m->render();
}

//Load
void Model::load(std::string path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Root::getInstance()->printOutput(import.GetErrorString());
		Root::getInstance()->printOutput("\n");
		return;
	}

	processNode(scene->mRootNode, scene);
}

//Process Node
void Model::processNode(aiNode * node, const aiScene *scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
		processMesh(scene->mMeshes[node->mMeshes[i]]);
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}

//Process Mesh
void Model::processMesh(aiMesh * mesh)
{
	Mesh* m = new Mesh();

	//Add Vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		glm::vec3 pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		glm::vec3 nor = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		//std::cout << "pos " << pos.x << " " << pos.y << " " << pos.z << std::endl;

		glm::vec2 tex = glm::vec2(0, 0);
		if (mesh->mTextureCoords[0])
			tex = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

		m->addVertex(new Vertex(pos,nor,tex) );
	}

	//Indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			m->addIndex(face.mIndices[j]);
	}

	m->compile();
	m_meshes.push_back(m);
}

//Clear Mesh
void Model::clearMesh()
{
	for (Mesh* m : m_meshes)
		delete m;
	m_meshes.clear();
}

//Get Model Rotation Matrix
glm::mat4 Model::getModelRotationMatrix() const
{
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_position->value);
	modelMatrix = glm::scale(modelMatrix, m_scale->value);
	modelMatrix = glm::rotate(modelMatrix, m_rotation->value.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, m_rotation->value.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, m_rotation->value.z, glm::vec3(0.0f, 0.0f, 1.0f));

	return modelMatrix;
}

//Get Rotation Matrix
glm::mat4 Model::getRotationMatrix() const
{
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), m_rotation->value.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, m_rotation->value.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, m_rotation->value.z, glm::vec3(0.0f, 0.0f, 1.0f));

	return rotationMatrix;
}

//Create an OrthoRect Inverted
Mesh* Model::orthoRectInverted() const
{
	Mesh* m = new Mesh();

	m->addVertex(new Vertex( glm::vec3(0, 0, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1, 1) ) );
	m->addVertex(new Vertex( glm::vec3(1, 1, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0, 0) ) );
	m->addVertex(new Vertex( glm::vec3(0, 1, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1, 0) ) );

	m->addIndex(0);
	m->addIndex(1);
	m->addIndex(2);
	m->addIndex(0);
	m->addIndex(2);
	m->addIndex(3);

	m->compile();
	return m;
}

//Set Position
void Model::setPosition(glm::vec3 pos)
{
	m_position->value = pos;
}

//Set Rotation
void Model::setRotation(glm::vec3 rot)
{
	m_rotation->value = rot;
}

//Set Scale
void Model::setScale(glm::vec3 scale)
{
	m_scale->value = scale;
}

//Get Position
glm::vec3 Model::getPosition() const
{
	return m_position->value;
}

//Get Rotation
glm::vec3 Model::getRotation() const
{
	return m_rotation->value;
}

//Get Scale
glm::vec2 Model::getScale() const
{
	return m_scale->value;
}
