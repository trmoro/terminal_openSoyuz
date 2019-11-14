#include "core/SType.h"
#include "core/Root.h"

//Constructor
SType::SType()
{
	name = "unnamed_object";
	type = "object";

	m_parent = nullptr;
	m_children = std::vector<SType*>();

	m_config = nullptr;
	m_isConfigCreated = false;
}

//Destructor
SType::~SType()
{

}

//Get Parent
SType* SType::getParent() const
{
	return m_parent;
}

//Set Parent
void SType::setParent(SType* parent)
{
	//If parent is all ready set
	//if (m_parent != nullptr)
	//	m_parent->getChildren().

	//Set Parent
	m_parent = parent;
	m_parent->m_children.push_back(this);
}

//Get Children
std::vector<SType*> SType::getChildren() const
{
	return m_children;
}

//Get Children Name
std::vector<std::string> SType::getChildrenName() const
{
	//Return value
	std::vector<std::string> ret = std::vector<std::string>();

	//Add Name
	for (SType* s : getChildren() )
		ret.push_back(s->name);

	//Return
	return ret;
}

//Get Children Type
std::vector<std::string> SType::getChildrenType() const
{
	//Return value
	std::vector<std::string> ret = std::vector<std::string>();

	//Add Name
	for (SType* s : getChildren() )
		ret.push_back(s->type);

	//Return
	return ret;
}

//Sort Children
//option = abc | type
void SType::sortChildren(std::string option)
{
	//Alphabetic
	if (option == "abc")
		sortABC();
	//Type
	else if (option == "type")
		sortType();
}

//PopBack Children
void SType::popBackChildren(unsigned int n)
{
	for (unsigned int i = 0; i < n; i++)
	{
		if (m_children.size() > 0)
		{
			delete m_children.at(m_children.size() - 1);
			m_children.pop_back();
		}
	}
}

//Base Print
std::string SType::print(std::string options) const 
{ 
	return options; 
}

//Base ToString
std::string SType::toString(std::string options) const
{
	return options;
}


//Base SetWithString
void SType::setWithString(std::string str)
{

}

//Base Use
void SType::use(std::string options)
{
	
}

//Update
void SType::update()
{

}

//Render
void SType::render()
{

}

//Cast
SType* SType::cast(SType* obj)
{
	return new SType();
}

//New
SType* SType::newType(std::vector<std::string> args)
{
	SType* st = new SType();
	st->name = "unnamed_object";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Type
	if (args.size() > 2)
		st->type = args[2];

	return st;
}

//Search toString
std::string SType::searchToString(std::string s, SType* from)
{
	//Return string
	std::string ret = s;

	//Search § (toString char)
	size_t start_pos = ret.find('§');

	//While we find it
	while (start_pos != std::string::npos)
	{
		//Path
		std::string path = "";

		//While there is no space, add to path
		unsigned cursor = start_pos + 1;
		while (cursor < ret.size() && ret[cursor] != ' ')
		{
			path += ret[cursor];
			cursor++;
		}

		//Test path and replace
		SType* obj = Root::getInstance()->getObject(path, from);
		if (obj != nullptr)
			ret.replace(start_pos - 1, 2 + path.size(), obj->toString(""));

		//Find another toString
		start_pos = ret.find('§', start_pos + path.size() + 1);
	}

	//Return
	return ret;
}

//Sort by Alphabetic Order
void SType::sortABC()
{
	//Sort Names
	std::vector<std::string> names = getChildrenName();
	std::sort(names.begin(), names.end());

	//Sort Children
	std::vector<SType*> sortedChildren = std::vector<SType*>();
	for (std::string s : names)
	{
		for (SType* st : m_children)
		{
			if (st->name == s)
				sortedChildren.push_back(st);
		}
	}

	//Replace
	m_children = sortedChildren;

}

//Sort By Type
void SType::sortType()
{

}

//Get Config
SType* SType::getConfig() const
{
	return m_config;
}

//Create Config
void SType::createConfig()
{
	//Add config object
	m_config = new SText("default");
	m_config->name = "config";
	m_config->type = "config_object";
	m_config->setParent(this);
	m_isConfigCreated = true;
}

//Is Config Created
bool SType::isConfigCreated() const
{
	return m_isConfigCreated;
}