#include "type/SScript.h"
#include "core/Root.h"

//Tokens Behaviour
constexpr unsigned int BLOCK		= 0;
constexpr unsigned int PASS			= 1;
constexpr unsigned int BLOCKPASS	= 2;
constexpr unsigned int LOOP			= 3;

//Static Variables used to init and get tokens
bool SScript::StaticInit = false;
std::map<std::string, unsigned int(*)(std::string)> SScript::TokenMap = std::map<std::string, unsigned int(*)(std::string)>();

//If Token
unsigned int If_Token(std::string value)
{
	if ( SScript::analyseBoolExpr(value) )
		return PASS;
	else
		return BLOCK;
}

//ElseIf
unsigned int ElseIf_Token(std::string value)
{
	if (If_Token(value) == PASS)
		return BLOCKPASS;
	else
		return BLOCK;
}

//Else Token
unsigned int Else_Token(std::string value)
{
	return BLOCKPASS;
}

//While Token
unsigned int While_Token(std::string value)
{
	if (If_Token(value) == PASS)
		return LOOP;
	else
		return BLOCK;
}

//Comment Token
unsigned int Comment_Token(std::string value)
{
	return PASS;
}


//Load Token
void SScript::LoadTokens()
{
	//Load
	TokenMap["if"]		= If_Token;
	TokenMap["elseif"]	= ElseIf_Token;
	TokenMap["else"]	= Else_Token;
	TokenMap["while"]	= While_Token;
	TokenMap["#"]		= Comment_Token;

	//Set Initialization to true
	StaticInit = true;
}

////////////////////////////////////SScript Inner Code

//Constructor
SScript::SScript()
{
	//Set type
	type = "script";

	//Static init
	if (!StaticInit)
		LoadTokens();

	//Self-init
	m_lines = std::vector<ScriptLine*>();
}

//Destructor
SScript::~SScript()
{
	//Delete all script line
	for (ScriptLine* l : m_lines)
		delete l;
	m_lines.clear();
}

//Add Line
void SScript::addLine(std::string str)
{
	//Detect first space
	std::string token = "";
	std::string value = "";
	bool tokenTaken = false;
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (!tokenTaken && str[i] != ' ')
			token.push_back(str[i]);
		else if (!tokenTaken && str[i] == ' ')
			tokenTaken = true;
		else
			value.push_back(str[i]);
	}

	//Add Line
	m_lines.push_back(new ScriptLine{token,value,0} );
}

//Level Analysis
void SScript::levelAnalysis()
{
	//For all lines
	unsigned int level = 0;
	for (ScriptLine* l : m_lines)
	{
		//Set Level
		l->level = level;

		//Check for opening tokens
		std::map<std::string, unsigned int(*)(std::string)>::iterator it;
		it = TokenMap.find(l->token);

		//Opening Token Found
		if (it != TokenMap.end())
			level++;

		//Check for end/closing token
		if (l->token == "end")
			level--;

		//Detect Error
		if (level < 0)
			Root::getInstance()->printOutput("Script Error : level below 0\n");

	}
}

//Check by launching all analyser
void SScript::check()
{
	levelAnalysis();
}

//Execute
void SScript::execute()
{
	std::cout << "script executed\n";

	//Block line level
	int blockLevel = -1;

	//Looping line
	std::vector<int> loopingLines = std::vector<int>();

	//For all line
	for (unsigned int i = 0; i < m_lines.size(); i++)
	{
		//Current ScriptLine
		ScriptLine* l = m_lines[i];

		//Level isn't blocked ? 
		if (blockLevel < 0 && l->level < blockLevel)
		{
			//Find Opening Tokens
			std::map<std::string, unsigned int(*)(std::string)>::iterator it;
			it = TokenMap.find(l->token);

			//Token Exists
			if (it != TokenMap.end())
			{
				//Block if Token returns BLOCK
				if (TokenMap[l->token](l->value) == BLOCK)
					blockLevel = l->level + 1;
				//Release level block if BLOCKPASSING Token pass
				else if (blockLevel == l->level + 1 && TokenMap[l->token](l->value) == BLOCKPASS)
					blockLevel = -1;
				//Loop
				else if (TokenMap[l->token](l->value) == LOOP)
					loopingLines.push_back(i);

				//
			}

			//End Token (Closing Token) and not looping -> unlock levels
			else if (l->token == "end" && loopingLines.empty() )
				blockLevel = -1;
			//End Token and looping, return to the line before looping line
			else if (l->token == "end")
			{
				i = loopingLines.back() - 1;
				loopingLines.pop_back();
			}

			//No token
			else
			{
				std::cout << "dir exec\n";

				//Execute line and unlock levels
				Root::getInstance()->execute(l->token, l->value);
				blockLevel = -1;
			}
		}

		//
	}
}

//To String
std::string SScript::toString(std::string options) const
{
	//Return all the lines
	std::string str = "";
	for (ScriptLine* s : m_lines)
		str += s->token + " " + s->value + "\n";

	return str;
}

//Set With String
void SScript::setWithString(std::string str)
{
	//Clear
	m_lines.clear();

	std::vector<std::string> lines = Root::splitString(str, "\n");
	for (std::string l : lines)
		addLine(l);

	//Check
	check();
}

//Analyse Boolean Expression
bool SScript::analyseBoolExpr(std::string s)
{
	/*Function is reading string like
	if a > b
	if a > b, b < c
	if pass 2 : a > b, b < c, c > a 
	if pass all : a > b, b < c, c > a 
	*/

	//Split pass number and conditions
	std::vector<std::string> pn_c = Root::splitString(s, ":");

	//Conditions vector
	std::vector<std::string> cv;

	//Pass number is set ?
	unsigned int pass_number;
	if (pn_c.size() > 1)
	{
		//Set condition vector
		cv = Root::splitString(pn_c[1], ",");

		//Split pass token and pass number
		std::vector<std::string> pt_pn = Root::splitString(pn_c[0], " ");
		
		//Detect pass number
		if (pt_pn[0] == "pass")
		{
			//All
			if (pt_pn[1] == "all")
				pass_number = cv.size();
			else
				pass_number = atoi(pt_pn[1].c_str() );
		}
	}
	//No pass number ?
	else if (pn_c.size() == 1)
	{
		cv = Root::splitString(pn_c[0], ",");
		pass_number = cv.size();
	}

	//Test conditions
	unsigned int testPassed = 0;
	for (std::string condition : cv)
	{
		//Get A operator B
		std::vector<std::string> a_op_b = Root::splitString(condition, " ");

		//Test
		if (a_op_b.size() > 2)
			if (SScript::testOn(a_op_b[0], a_op_b[1], a_op_b[2]))
				testPassed++;

		//Enough test passed ?
		if (testPassed == pass_number)
			return true;
	}

	//Return false
	return false;
}

//Test Operation on 2 SType
bool SScript::testOn(std::string strA, std::string op, std::string strB)
{
	//Detect object/value
	SType* a = Root::getInstance()->getObject(strA, Root::getInstance()->getCurrentObject()->getParent() );
	SType* b = Root::getInstance()->getObject(strB, Root::getInstance()->getCurrentObject()->getParent() );

	//Test operator
	if (op == "=")
		return a->isEqu(b);
	else if (op == ">")
		return a->isSup(b);
	else if (op == "<")
		return a->isInf(b);
	else if (op == ">=")
		return a->isSupEqu(b);
	else if (op == "<=")
		return a->isInf(b);
	else if (op == "!=")
		return a->isNotEqu(b);
	else
		return false;
}