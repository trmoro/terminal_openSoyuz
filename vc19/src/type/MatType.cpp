#include "type/MatType.h"
#include "core/Root.h"

//SMat4 ToString
std::string SMat4::toString(std::string options) const
{
	std::string str = "";

	for (unsigned int x = 0; x < value.length(); x++)
	{
		for (unsigned int y = 0; y < value[x].length(); y++)
			str += std::to_string(value[x][y]) + " ";
	}

	return str;
}

//SMat4 Print
std::string SMat4::print(std::string options) const
{
	std::string str = "\n";

	for (unsigned int y = 0; y < value.length(); y++)
	{
		for (unsigned int x = 0; x < value[y].length(); x++)
			str += std::to_string(value[x][y]) + "\t";
		str += "\n";
	}

	return str;
}

//SMat4 Set With String
void SMat4::setWithString(std::string str)
{
	//Split
	std::vector<std::string> v = Root::splitString(searchToString(str, Root::getInstance()->getCurrentObject()), " ");

	//Set Case Value
	unsigned step = 0;
	while (step < v.size() && step < 16)
	{
		//Set
		value[step / 4][step % 4] = std::atof(v[step].c_str() );

		//Increase Step
		step++;
	}

}

//SMat4 Cast
SMat4* SMat4::cast(SType* obj)
{
	if (obj->type == "mat4")
		return (SMat4*)obj;
	else
		return new SMat4(glm::mat4());
}

//SMat4 New
SType* SMat4::newType(std::vector<std::string> args)
{
	//New
	SMat4* st = new SMat4(glm::mat4());
	st->name = "unnamed_mat4";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Value : concatenate all the rest
	if (args.size() > 2)
	{
		std::string conc = "";
		for (unsigned int i = 2; i < args.size(); i++)
			conc += args[i] + " ";
		st->setWithString(conc);
	}

	return st;
}

//SMat3 ToString
std::string SMat3::toString(std::string options) const
{
	std::string str = "";

	for (unsigned int x = 0; x < value.length(); x++)
	{
		for (unsigned int y = 0; y < value[x].length(); y++)
			str += std::to_string(value[x][y]) + " ";
	}

	return str;
}

//SMat3 Print
std::string SMat3::print(std::string options) const
{
	std::string str = "\n";

	for (unsigned int y = 0; y < value.length(); y++)
	{
		for (unsigned int x = 0; x < value[y].length(); x++)
			str += std::to_string(value[x][y]) + "\t";
		str += "\n";
	}

	return str;
}

//SMat3 Set With String
void SMat3::setWithString(std::string str)
{
	//Split
	std::vector<std::string> v = Root::splitString(searchToString(str, Root::getInstance()->getCurrentObject()), " ");

	//Set Case Value
	unsigned step = 0;
	while (step < v.size() && step < 9)
	{
		//Set
		value[step / 3][step % 3] = std::atof(v[step].c_str());

		//Increase Step
		step++;
	}

}

//SMat3 Cast
SMat3* SMat3::cast(SType* obj)
{
	if (obj->type == "mat3")
		return (SMat3*)obj;
	else
		return new SMat3(glm::mat3());
}

//SMat3 New
SType* SMat3::newType(std::vector<std::string> args)
{
	//New
	SMat3* st = new SMat3(glm::mat3());
	st->name = "unnamed_mat3";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Value : concatenate all the rest
	if (args.size() > 2)
	{
		std::string conc = "";
		for (unsigned int i = 2; i < args.size(); i++)
			conc += args[i] + " ";
		st->setWithString(conc);
	}

	return st;
}

//SMat2 ToString
std::string SMat2::toString(std::string options) const
{
	std::string str = "";

	for (unsigned int x = 0; x < value.length(); x++)
	{
		for (unsigned int y = 0; y < value[x].length(); y++)
			str += std::to_string(value[x][y]) + " ";
	}

	return str;
}

//SMat2 Print
std::string SMat2::print(std::string options) const
{
	std::string str = "\n";

	for (unsigned int y = 0; y < value.length(); y++)
	{
		for (unsigned int x = 0; x < value[y].length(); x++)
			str += std::to_string(value[x][y]) + "\t";
		str += "\n";
	}

	return str;
}

//SMat2 Set With String
void SMat2::setWithString(std::string str)
{
	//Split
	std::vector<std::string> v = Root::splitString(searchToString(str, Root::getInstance()->getCurrentObject()), " ");

	//Set Case Value
	unsigned step = 0;
	while (step < v.size() && step < 4)
	{
		//Set
		value[step / 2][step % 2] = std::atof(v[step].c_str());

		//Increase Step
		step++;
	}

}

//SMat2 Cast
SMat2* SMat2::cast(SType* obj)
{
	if (obj->type == "mat2")
		return (SMat2*)obj;
	else
		return new SMat2(glm::mat2());
}

//SMat4 New
SType* SMat2::newType(std::vector<std::string> args)
{
	//New
	SMat2* st = new SMat2(glm::mat2());
	st->name = "unnamed_mat2";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Value : concatenate all the rest
	if (args.size() > 2)
	{
		std::string conc = "";
		for (unsigned int i = 2; i < args.size(); i++)
			conc += args[i] + " ";
		st->setWithString(conc);
	}

	return st;
}