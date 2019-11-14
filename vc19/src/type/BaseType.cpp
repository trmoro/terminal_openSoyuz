#include "type/BaseType.h"
#include "core/Root.h"

//SInt Cast
SInt* SInt::cast(SType* obj)
{
	if (obj->type == "int")
		return (SInt*)obj;
	else if (obj->type == "float")
		return new SInt(SFloat::cast(obj)->value);
	else if (obj->type == "boolean")
		return new SInt(SBool::cast(obj)->value);
	else
		return new SInt(0);
}

//SInt New
SType* SInt::newType(std::vector<std::string> args)
{
	//New
	SInt* st = new SInt(0);
	st->name = "unnamed_int";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Value
	if (args.size() > 2)
		st->setWithString(args[2]);

	return st;
}

//SInt SetWithString
void SInt::setWithString(std::string str) 
{ 
	value = std::atoi(searchToString(str, Root::getInstance()->getCurrentObject()).c_str()); 
}

//SFloat Cast
SFloat* SFloat::cast(SType* obj)
{
	if (obj->type == "float")
		return (SFloat*)obj;
	else if (obj->type == "int")
		return new SFloat(SInt::cast(obj)->value);
	else
		return new SFloat(0);
}

//SFloat New
SType* SFloat::newType(std::vector<std::string> args)
{
	//New
	SFloat* st = new SFloat(0);
	st->name = "unnamed_float";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Value
	if (args.size() > 2)
		st->setWithString(args[2]);

	return st;
}

//SFloat SetWithString
void SFloat::setWithString(std::string str)
{ 
	value = std::atof(searchToString(str, Root::getInstance()->getCurrentObject()).c_str()); 
}

//SBool Cast
SBool* SBool::cast(SType* obj)
{
	if (obj->type == "boolean")
		return (SBool*)obj;
	else if (obj->type == "int")
		return new SBool(SInt::cast(obj)->value > 0);
	else if (obj->type == "float")
		return new SBool(SFloat::cast(obj)->value > 0);
	else
		return new SBool(false);

}

//SBool New
SType* SBool::newType(std::vector<std::string> args)
{
	//New
	SBool* st = new SBool(false);
	st->name = "unnamed_bool";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Value
	if (args.size() > 2)
		st->setWithString(args[2]);

	return st;
}

//SBool SetWithString
void SBool::setWithString(std::string str)
{
	if (searchToString(str, Root::getInstance()->getCurrentObject()) == "true") 
		value = true; 
	else 
		value = false;
}

//SText Cast
SText* SText::cast(SType* obj)
{
	if (obj->type == "text")
		return (SText*)obj;
	else
		return new SText(obj->toString(""));
}

//SText New
SType* SText::newType(std::vector<std::string> args)
{
	//New
	SText* st = new SText("");
	st->name = "unnamed_text";

	//Name
	if (args.size() > 1)
		st->name = args[1];

	//Value
	if (args.size() > 2)
		st->setWithString(args[2]);

	return st;
}

//SText SetWithString
void SText::setWithString(std::string str)
{
	value = searchToString(str, Root::getInstance()->getCurrentObject());
}

//SPointer Cast
SPointer * SPointer::cast(SType* obj)
{
	if (obj->type == "pointer")
		return (SPointer*)obj;
	else
		return new SPointer(obj);
}

//SPointer New
SType* SPointer::newType(std::vector<std::string> args)
{
	//New
	SPointer* sp = new SPointer(nullptr);
	sp->name = "unnamed_pointer";

	//Name
	if (args.size() > 1)
		sp->name = args[1];

	//Value
	if (args.size() > 2)
		sp->value = Root::getInstance()->getObject(args[2], Root::getInstance()->getCurrentObject());

	return sp;
}