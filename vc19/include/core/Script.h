#pragma once

#pragma message ("core/Script Type is defined")

#include <map>

#include "core/SType.h"

struct Line
{
	std::string token;
	std::vector<std::string> values;
	unsigned int level;
};

class ResultMap
{
public:
	ResultMap();
	~ResultMap();
	std::map<std::string, SType*> value;
};

class Script
{
public:
	Script(std::string raw);
	~Script();
	
	//Execute script on an object
	ResultMap* execute(SType* current) const;
	
	//Convert Raw Text into Script Line
	void rawToLines();

	//Recursive Function to get all children, including children children
	static void getAllChildren(SType* parent, std::string path, std::string type, ResultMap* rm);

	//Tokens and Condition
	static std::map<std::string, void(*)(ResultMap*, SType*, std::string)> TokenMap;
	static std::map<std::string, int(*)(SType*)> ConditionMap;

	//Load Token and Condition
	static void LoadToken();
	static bool areTokenLoaded;

private:

	//Recursive function to convert a raw line into script line
	Line textlineToLine(std::string l, unsigned int level) const;

	//Script Line and Raw Text
	std::vector<Line> m_lines;
	std::string m_raw;
};