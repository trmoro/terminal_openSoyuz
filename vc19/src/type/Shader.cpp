#include "type/Shader.h"

#include "core/Root.h"

//Create
Shader::Shader() : SType()
{
	//Vertex
	m_vertex = new SText("");
	m_vertex->name = "vertex";
	m_vertex->setParent(this);

	//Fragment
	m_fragment = new SText("");
	m_fragment->name = "fragment";
	m_fragment->setParent(this);

	//Geometry
	m_geometry = new SText("");
	m_geometry->name = "geometry";
	m_geometry->setParent(this);

	//Use Geometry
	m_useGeometry = new SBool(false);
	m_useGeometry->name = "useGeometry";
	m_useGeometry->setParent(this);
}

//Delete
Shader::~Shader()
{

}

//To String
std::string Shader::toString(std::string options) const
{
	return "";
}

//Print
std::string Shader::print(std::string options) const
{
	return "";
}

//Set With String
void Shader::setWithString(std::string str)
{

}

//Cast
Shader* Shader::cast(SType* obj)
{
	return nullptr;
}

//New Shader
SType* Shader::newType(std::vector<std::string> args)
{
	return nullptr;
}

//Generate Shader
void Shader::generate()
{
	//Convert to const GLchar*
	const GLchar* vs = m_vertex->value.c_str();
	const GLchar* gs = m_geometry->value.c_str();
	const GLchar* fs = m_fragment->value.c_str();

	//Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vs, NULL);
	glCompileShader(vertexShader);

	//Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		Root::getInstance()->printOutput("ERROR : Vertex Shader Compilation FAILED !\n");
		Root::getInstance()->printOutput(infoLog);
	}

	//Geometry shader
	GLuint geometryShader;
	if (m_useGeometry)
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &gs, NULL);
		glCompileShader(geometryShader);

		//Check for compile time errors
		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
			Root::getInstance()->printOutput("ERROR : Geometry Shader Compilation FAILED !\n");
			Root::getInstance()->printOutput(infoLog);
		}
	}

	//Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fs, NULL);
	glCompileShader(fragmentShader);

	//Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		Root::getInstance()->printOutput("ERROR : Fragment Shader Compilation FAILED !\n");
		Root::getInstance()->printOutput(infoLog);
	}

	//Link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	if(m_useGeometry)
		(shaderProgram, geometryShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		Root::getInstance()->printOutput("ERROR : Linking Failed !\n");
		Root::getInstance()->printOutput(infoLog);
	}

	//Delete Shader
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);

	//Return Program
	m_id = shaderProgram;
}

//Set Uniform for Int
void Shader::setUniformi(GLchar * uniform, int value) const
{
	GLuint loc = glGetUniformLocation(m_id, uniform);
	glUniform1i(loc, value);
}

//Set Uniform for Float
void Shader::setUniformf(GLchar * uniform, float value) const
{
	GLuint loc = glGetUniformLocation(m_id, uniform);
	glUniform1f(loc, value);
}

//Vector 2
void Shader::setUniformVec2(GLchar * uniform, glm::vec2 value) const
{
	GLuint loc = glGetUniformLocation(m_id, uniform);
	glUniform2f(loc, value.x, value.y);
}

//Vector 3
void Shader::setUniformVec3(GLchar * uniform, glm::vec3 value) const
{
	GLuint loc = glGetUniformLocation(m_id, uniform);
	glUniform3f(loc, value.x, value.y, value.z);
}

//Set Uniform for vec4
void Shader::setUniformVec4(GLchar * uniform, glm::vec4 value) const
{
	GLuint loc = glGetUniformLocation(m_id, uniform);
	glUniform4f(loc, value.x, value.y, value.z, value.w);
}

//Set Uniform for Matrix4x4
void Shader::setUniformMatrix4(GLchar * uniform, glm::mat4 value) const
{
	GLuint matrixID = glGetUniformLocation(m_id, uniform);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &value[0][0]);
}

//Use
void Shader::use(std::string s)
{
	if (s == "gen" || s == "generate")
		generate();
}

//Get ID
GLuint Shader::getID() const
{
	return m_id;
}

//Get Vertex
SText* Shader::getVertex() const
{
	return m_vertex;
}

//Get Fragment
SText* Shader::getFragment() const
{
	return m_fragment;
}

//Get Geometry
SText* Shader::getGeometry() const
{
	return m_geometry;
}

//Use Geometry
void Shader::useGeometry(bool b)
{
	m_useGeometry->value = b;
}
