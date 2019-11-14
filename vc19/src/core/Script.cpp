#include "core/Script.h"
#include "core/Root.h"

//Static Variable : Token
std::map<std::string, void(*)(ResultMap*, SType*, std::string)> Script::TokenMap = std::map<std::string, void(*)(ResultMap*, SType*, std::string)>();
std::map<std::string, int(*)(SType*)> Script::ConditionMap = std::map<std::string, int(*)(SType*)>();
bool Script::areTokenLoaded = false;

//Select Token
void TokenSelect(ResultMap* rm, SType* st, std::string value)
{
	//All
	if (value == "*" || value == "all")
		Script::getAllChildren(st, "", "*", rm);
	//Other type
	else
		Script::getAllChildren(st, "", value, rm);
}

//On Token
void TokenOn(ResultMap* rm, SType* st, std::string value)
{
	SType* s = Root::getInstance()->getObject(value, st);
	if (s != nullptr)
		rm->value[value] = s;
}

//From Token
void TokenFrom(ResultMap* rm, SType* st, std::string value)
{
	//Objects to remove
	std::vector<std::string> removeList = std::vector<std::string>();

	//Find
	std::map<std::string, SType*>::iterator it;
	for (it = rm->value.begin(); it != rm->value.end(); it++)
	{
		if (it->first.find(value) != 0)
			removeList.push_back(it->first);
	}

	//Remove
	for (std::string s : removeList)
		rm->value.erase(s);
}

//Where Token
//Value : condition value
void TokenWhere(ResultMap* rm, SType* st, std::string value)
{
	//Objects to remove
	std::vector<std::string> removeList = std::vector<std::string>();

	//Separate Condition and Values
	//std::strin

	//Find
	std::map<std::string, SType*>::iterator it;
	for (it = rm->value.begin(); it != rm->value.end(); it++)
	{
		if (Script::ConditionMap[value](st) == 0)
			removeList.push_back(it->first);
	}

	//Remove
	for (std::string s : removeList)
		rm->value.erase(s);
}

///Class Code

//Constructor
Script::Script(std::string raw)
{
	//Load Token
	if (!areTokenLoaded)
		LoadToken();

	m_lines = std::vector<Line>();
	m_raw = raw;
	rawToLines();
}

//Destructor
Script::~Script()
{
}

//Load Token
void Script::LoadToken()
{
	TokenMap["select"]	= TokenSelect;
	TokenMap["on"]		= TokenOn;
	TokenMap["from"]	= TokenFrom;
	TokenMap["where"]	= TokenWhere;

	areTokenLoaded = true;
}

//Execute Script
ResultMap* Script::execute(SType * current) const
{
	//Map storing SType corresponding to the query
	ResultMap* result_map = new ResultMap();

	//Execute Lines
	for (Line l : m_lines)
	{

	}

	return result_map;
}

//Convert Raw Text into Lines
void Script::rawToLines()
{
	//Read Text by lines
	std::vector<std::string> lines = Root::splitString(m_raw, "\n");
	for (std::string l : lines)
		m_lines.push_back(textlineToLine(l, 0));
}

//Convert line text to a script line
Line Script::textlineToLine(std::string l, unsigned int level) const
{
	//Tabulation ? New level
	if (l[0] = '\t')
		return textlineToLine(l.substr(1, l.size() - 1), level + 1);
	
	//Separate token and values
	std::vector<std::string> words = Root::splitString(l, " ");
	if (words.size() > 0)
	{
		std::vector<std::string> values = std::vector<std::string>();
		for (unsigned int i = 1; i < words.size(); i++)
			values.push_back(words[i]);
		return Line{ words[0],values,level };
	}
	else
		return Line{ "not_a_line" };
}

//Get All Children
void Script::getAllChildren(SType* parent, std::string path, std::string type, ResultMap* rm)
{
	for (SType* st : parent->getChildren())
	{
		//Add current child
		if(type == "*" || st->type == type)
			rm->value[st->name] = st;

		getAllChildren(st, st->name + ".", type, rm);
	}
}

//ResultMap Constructor
ResultMap::ResultMap()
{
	value = std::map<std::string, SType*>();
}

//Result Map Destructor
ResultMap::~ResultMap()
{
}