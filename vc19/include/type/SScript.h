#pragma once

#include "core/SType.h"
#pragma message ("type/SScript is defined")

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct ScriptLine
{
	std::string token;
	std::string value;
	unsigned int level;
};

class SScript : public SType
{
public:
	//Constructor and Destructor
	SScript();
	~SScript();

	//Add Line
	void addLine(std::string str);

	//Analysers
	void levelAnalysis();
	void check();

	//Execute Script
	void execute();

	//To String and Set With String (Parent Function)
	std::string toString(std::string options) const override;
	void setWithString(std::string str) override;

	//Static function
	static bool analyseBoolExpr(std::string s);
	static bool testOn(std::string strA, std::string op, std::string strB);

private:

	std::vector<ScriptLine*> m_lines;

	static bool StaticInit;
	static void	LoadTokens();
	static std::map<std::string, unsigned int(*)(std::string)> TokenMap;

};