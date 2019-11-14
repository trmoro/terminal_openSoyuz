#include "type/Vertex.h"
#include "core/Root.h"

//Constructor
Vertex::Vertex(SVec3* position, SVec3* normal, SVec2* texture_uv) : SType(), m_position(position), m_normal(normal), m_texture_uv(texture_uv)
{
	type = "vertex";
	renameChildren();
}

Vertex::Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 uv) : Vertex(new SVec3(pos),new SVec3(normal), new SVec2(uv) )
{

}

//Vertex To String
std::string Vertex::toString(std::string options) const
{
	return "POSITION\n" + m_position->toString("")
		+ "\n\nNORMAL\n" + m_normal->toString("")
		+ "\n\nTEXTURE COORDINATE\n" + m_texture_uv->toString("");
};

//Vertex Set With String
void Vertex::setWithString(std::string str)
{
	//Split
	std::vector<std::string> v = Root::splitString(searchToString(str, Root::getInstance()->getCurrentObject()), " ");

	//Position
	if (v.size() == 4 && v[0] == "position")
	{
		m_position = new SVec3(glm::vec3() );
		m_position->setWithString(v[1] + " " + v[2] + " " + v[3]);
		m_position->setParent(this);
		m_position->name = "position";
	}
	//Normal
	if (v.size() == 4 && v[0] == "normal")
	{
		m_normal = new SVec3(glm::vec3());
		m_normal->setWithString(v[1] + " " + v[2] + " " + v[3]);
		m_normal->setParent(this);
		m_normal->name = "normal";
	}
	//Texture UV
	if (v.size() == 3 && v[0] == "texture_uv")
	{
		m_texture_uv = new SVec2(glm::vec3());
		m_texture_uv->setWithString(v[1] + " " + v[2]);
		m_texture_uv->setParent(this);
		m_texture_uv->name = "texture_uv";
	}
	//Copy
	if (v.size() > 1 && v[0] == "copy")
	{

	}
}

//Vertex Cast
Vertex* Vertex::cast(SType* obj)
{
	if (obj->type == "vertex")
		return (Vertex*)obj;
	else
		return new Vertex(new SVec3(glm::vec3()), new SVec3(glm::vec3()), new SVec2(glm::vec2()) );
}

//Vertex New
SType* Vertex::newType(std::vector<std::string> args)
{
	//New
	Vertex* st = new Vertex(new SVec3(glm::vec3()), new SVec3(glm::vec3()), new SVec2(glm::vec2()));
	st->name = "unnamed_vertex";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Set with string
	if (args.size() > 2)
	{
		std::string str = "";
		for (unsigned int i = 2; i < args.size(); i++)
			str += args[i] + " ";
		st->setWithString(str);
	}

	return st;
}

//Use
void Vertex::use(std::string options)
{
	if (options == "renameChildren")
		renameChildren();
}

//Rename Children
void Vertex::renameChildren()
{
	m_position->name = "position";
	m_position->setParent(this);

	m_normal->name = "normal";
	m_normal->setParent(this);

	m_texture_uv->name = "texture_uv";
	m_texture_uv->setParent(this);
}