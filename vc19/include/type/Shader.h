#pragma once
#pragma message ("type/Shader Type is defined")

#include "core/SType.h"
#include "type/BaseType.h"

#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>

class Shader : public SType
{
public:
	//Constructor and Destructor
	Shader();
	~Shader();

	//To String, Print and Set With String
	std::string toString(std::string options) const override;
	std::string print(std::string options) const override;
	void setWithString(std::string str) override;

	//Static Functions : Cast and New
	static Shader* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Override Use
	void use(std::string s) override;

	//Generate Shader
	void generate();

	//Uniform settings
	void setUniformi(GLchar * uniform, int value) const;
	void setUniformf(GLchar * uniform, float value) const;
	void setUniformVec2(GLchar * uniform, glm::vec2 value) const;
	void setUniformVec3(GLchar * uniform, glm::vec3 value) const;
	void setUniformVec4(GLchar * uniform, glm::vec4 value) const;
	void setUniformMatrix4(GLchar * uniform, glm::mat4 value) const;

	//Get ID
	GLuint getID() const;

	//Get Vertex, Fragment and Geometry
	SText* getVertex() const;
	SText* getFragment() const;
	SText* getGeometry() const;

	//Use Geometry
	void useGeometry(bool b);

private:

	//Id
	GLuint m_id;

	//Shader
	SText* m_vertex;
	SText* m_fragment;
	SText* m_geometry;
	SBool* m_useGeometry;

};

