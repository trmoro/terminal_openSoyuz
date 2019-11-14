#include "type/VecType.h"
#include "core/Root.h"

//SVec4 To String
std::string SVec4::toString(std::string options) const
{
	return std::to_string(value.x) + " " + std::to_string(value.y) + " " + std::to_string(value.z) + " " + std::to_string(value.w);
}

//SVec4 Print
std::string SVec4::print(std::string options) const
{
	return "x : " + std::to_string(value.x)
		+ "\ny : " + std::to_string(value.y)
		+ "\nz : " + std::to_string(value.z)
		+ "\nw : " + std::to_string(value.w);
}

//SVec4 Set With String
void SVec4::setWithString(std::string str)
{
	//Split
	std::vector<std::string> v = Root::splitString(searchToString(str, Root::getInstance()->getCurrentObject()), " ");

	//X
	if (v.size() > 0)
		value.x = std::atof(v[0].c_str());

	//Y
	if (v.size() > 1)
		value.y = std::atof(v[1].c_str());

	//Z
	if (v.size() > 2)
		value.z = std::atof(v[2].c_str());

	//W
	if (v.size() > 3)
		value.w = std::atof(v[3].c_str());
}

//SVec4 Cast
SVec4* SVec4::cast(SType* obj)
{
	if (obj->type == "vec4")
		return (SVec4*)obj;
	else
		return new SVec4(glm::vec4());
}

//SVec4 New
SType* SVec4::newType(std::vector<std::string> args)
{
	//New
	SVec4* st = new SVec4(glm::vec4());
	st->name = "unnamed_vec4";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Value : X
	if (args.size() == 3)
		st->setWithString(args[2]);

	//Value : X Y
	if (args.size() == 4)
		st->setWithString(args[2] + " " + args[3]);

	//Value : X Y Z
	if (args.size() == 5)
		st->setWithString(args[2] + " " + args[3] + " " + args[4]);

	//Value : X Y Z W
	if (args.size() > 5)
		st->setWithString(args[2] + " " + args[3] + " " + args[4] + " " + args[5]);

	return st;
}

//SVec3 To String
std::string SVec3::toString(std::string options) const
{
	return std::to_string(value.x) + " " + std::to_string(value.y) + " " + std::to_string(value.z);
}

//SVec3 Print
std::string SVec3::print(std::string options) const 
{
	return "x : " + std::to_string(value.x) 
		+ "\ny : " + std::to_string(value.y)
		+ "\nz : " + std::to_string(value.z);
};

//SVec3 Set With String
void SVec3::setWithString(std::string str)
{
	//Split
	std::vector<std::string> v = Root::splitString(searchToString(str, Root::getInstance()->getCurrentObject()), " ");

	//X
	if(v.size() > 0)
		value.x = std::atof(v[0].c_str() );

	//Y
	if (v.size() > 1)
		value.y = std::atof(v[1].c_str());

	//Z
	if (v.size() > 2)
		value.z = std::atof(v[2].c_str());
}

//SVec3 Cast
SVec3* SVec3::cast(SType* obj)
{
	if (obj->type == "vec3")
		return (SVec3*)obj;
	else
		return new SVec3(glm::vec3());
}

//SVec3 New
SType* SVec3::newType(std::vector<std::string> args)
{
	//New
	SVec3* st = new SVec3(glm::vec3() );
	st->name = "unnamed_vec3";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Value : X
	if (args.size() == 3)
		st->setWithString(args[2]);

	//Value : X Y
	if (args.size() == 4)
		st->setWithString(args[2] + " " + args[3]);

	//Value : X Y Z
	if (args.size() > 4)
		st->setWithString(args[2] + " " + args[3] + " " + args[4]);

	return st;
}

// SVec2 To String
std::string SVec2::toString(std::string options) const
{
	return std::to_string(value.x) + " " + std::to_string(value.y);
}

// SVec2 Print
std::string SVec2::print(std::string options) const
{
	return "x : " + std::to_string(value.x)
		+ "\ny : " + std::to_string(value.y);
}

//SVec2 Set With String
void SVec2::setWithString(std::string str)
{
	//Split
	std::vector<std::string> v = Root::splitString(searchToString(str, Root::getInstance()->getCurrentObject()), " ");

	//X
	if (v.size() > 0)
		value.x = std::atof(v[0].c_str());

	//Y
	if (v.size() > 1)
		value.y = std::atof(v[1].c_str());
}

//SVec3 Cast
SVec2* SVec2::cast(SType* obj)
{
	if (obj->type == "vec2")
		return (SVec2*)obj;
	else
		return new SVec2(glm::vec2());
}

//SVec3 New
SType* SVec2::newType(std::vector<std::string> args)
{
	//New
	SVec2* st = new SVec2(glm::vec2());
	st->name = "unnamed_vec2";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Value : X
	if (args.size() == 3)
		st->setWithString(args[2]);

	//Value : X Y
	if (args.size() > 3)
		st->setWithString(args[2] + " " + args[3]);

	return st;
}