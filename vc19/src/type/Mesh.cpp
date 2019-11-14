#include "type/Mesh.h"
#include "core/Root.h"

//Constructor
Mesh::Mesh()
{
	type = "mesh";
	m_isCompiled = false;
	m_isCompilationNeeded = false;

	m_vertices = new SType();
	m_vertices->name = "vertices";
	m_vertices->type = "node_vertex";
	m_vertices->setParent(this);

	m_indices = new SType();
	m_indices->name = "indices";
	m_indices->type = "node_int";
	m_indices->setParent(this);

	m_vao = 0;
	m_vbo = 0;
	m_ebo = 0;

}

//Mesh To String
std::string Mesh::toString(std::string options) const
{
	return "Mesh";
}

//Mesh Set With String
void Mesh::setWithString(std::string str)
{
	//Split
	std::vector<std::string> v = Root::splitString(str, " ");
}

//Mesh Cast
Mesh* Mesh::cast(SType* obj)
{
	if (obj->type == "mesh")
		return (Mesh*)obj;
	else
		return new Mesh();
}

//Mesh New
SType* Mesh::newType(std::vector<std::string> args)
{
	//New
	Mesh* st = new Mesh();
	st->name = "unnamed_mesh";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	return st;
}

//Use
void Mesh::use(std::string options)
{
	//Compile
	if (options == "compile")
		m_isCompilationNeeded = true;
}

//Compile
void Mesh::compile()
{
	//Vertex Size
	unsigned int VERTEX_SIZE = 8;

	//Convert Data to OpenGL Data
	GLfloat *vertices = new GLfloat[m_vertices->getChildren().size() * VERTEX_SIZE];
	for (unsigned int i = 0; i < m_vertices->getChildren().size(); i++)
	{
		Vertex* v = Vertex::cast(m_vertices->getChildren()[i]);

		vertices[(i * VERTEX_SIZE) + 0] = v->m_position->value.x;
		vertices[(i * VERTEX_SIZE) + 1] = v->m_position->value.y;
		vertices[(i * VERTEX_SIZE) + 2] = v->m_position->value.z;
		vertices[(i * VERTEX_SIZE) + 3] = v->m_normal->value.x;
		vertices[(i * VERTEX_SIZE) + 4] = v->m_normal->value.y;
		vertices[(i * VERTEX_SIZE) + 5] = v->m_normal->value.z;
		vertices[(i * VERTEX_SIZE) + 6] = v->m_texture_uv->value.x;
		vertices[(i * VERTEX_SIZE) + 7] = v->m_texture_uv->value.y;
	}
	GLuint *indices = new GLuint[m_indices->getChildren().size()];
	for (unsigned int i = 0; i < m_indices->getChildren().size(); i++)
		indices[i] = SInt::cast(m_indices->getChildren()[i])->value;

	//Generate Buffer
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	//Bind Vertex Array
	glBindVertexArray(m_vao);

	//Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices->getChildren().size() * VERTEX_SIZE * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	//Indice Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices->getChildren().size() * sizeof(GLuint), indices, GL_STATIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GLfloat), (GLvoid *)0);

	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));

	//Texture Coordinate
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));

	//Unbind
	glBindVertexArray(0);

	//Clear
	delete[] vertices;

	//Set Compile
	m_isCompiled = true;
	m_isCompilationNeeded = false;
}

//Is Compilation Needed
bool Mesh::isCompilationNeeded() const
{
	return m_isCompilationNeeded;
}

//Update
void Mesh::update()
{
	if (isCompilationNeeded())
		compile();
}

//Render
void Mesh::render()
{
	//Is Compiled
	if (m_isCompiled)
	{

		//Bind VAO
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, m_indices->getChildren().size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}

//Add Vertex
void Mesh::addVertex(Vertex* v)
{
	v->name = "v_" + std::to_string(m_vertices->getChildren().size());
	v->setParent(m_vertices);
}

//Add Index
void Mesh::addIndex(unsigned int i)
{
	SInt* index = new SInt(i);
	index->name = "i_" + std::to_string(m_indices->getChildren().size());
	index->setParent(m_indices);
}

//PopBack Vertex
void Mesh::popBackVertex(unsigned int n)
{
	m_vertices->popBackChildren(n);
}

//PopBack Index
void Mesh::popBackIndex(unsigned int n)
{
	m_indices->popBackChildren(n);
}