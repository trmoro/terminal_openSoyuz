#pragma once

#include "core/SType.h"
#pragma message ("type/Mesh Type is defined")

#include <vector>
#include <GL/glew.h>

#include "type/BaseType.h"
#include "type/VecType.h"
#include "type/Vertex.h"

class Mesh : public SType
{
public:
	Mesh();

	//Vertices and Indices
	SType* m_vertices;
	SType* m_indices;

	//Mesh Functions
	void compile();
	void update() override;
	void render() override;

	//To String and Set With String
	std::string toString(std::string options) const override;
	void setWithString(std::string str) override;

	//Use
	void use(std::string options) override;

	//Add Vertex and Index
	void addVertex(Vertex* v);
	void addIndex(unsigned int i);

	//PopBack Vertex and Index
	void popBackVertex(unsigned int n);
	void popBackIndex(unsigned int n);

	//Static Functions : Cast and New
	static Mesh* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Is Compilation Needed
	bool isCompilationNeeded() const;
	
private:

	bool m_isCompiled, m_isCompilationNeeded;
	unsigned int m_vao, m_vbo, m_ebo;
};