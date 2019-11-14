#pragma once

#include "core/SType.h"
#pragma message ("type/Base Types are defined")

//Soyuz Int
class SInt : public SType
{
public:
	SInt(int i) : SType(), value(i) { type = "int"; }
	~SInt() {};
	int value;

	//Functions to convert to string and set with string
	std::string print(std::string options) const override { return "Value : " + std::to_string(value); };
	std::string toString(std::string options) const override { return std::to_string(value); };
	void setWithString(std::string str) override;

	//Static Functions : Cast and New
	static SInt* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { value = cast(a)->value; };
	virtual void add(SType* a) override { value += cast(a)->value; };
	virtual void min(SType* a) override { value -= cast(a)->value; };
	virtual void mul(SType* a) override { value *= cast(a)->value; };
	virtual void div(SType* a) override { value /= cast(a)->value; };
	virtual void mod(SType* a) override { value %= cast(a)->value; };

	//Operators returning operation over object
	virtual SInt* retAdd(SType* a) const override { return new SInt(value + cast(a)->value); };
	virtual SInt* retMin(SType* a) const override { return new SInt(value - cast(a)->value); };
	virtual SInt* retMul(SType* a) const override { return new SInt(value * cast(a)->value); };
	virtual SInt* retDiv(SType* a) const override { return new SInt(value / cast(a)->value); };
	virtual SInt* retMod(SType* a) const override { return new SInt(value % cast(a)->value); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { return value == cast(a)->value; };
	virtual bool isSup(SType* a) const override { return value > cast(a)->value; };
	virtual bool isInf(SType* a) const override { return value < cast(a)->value; };
};

//Soyuz Float
class SFloat : public SType
{
public:
	SFloat(float f) : SType(), value(f) { type = "float"; }
	~SFloat() {};
	float value;

	//Functions to convert to string and set with string
	std::string print(std::string options) const override { return "Value : " + std::to_string(value); };
	std::string toString(std::string options) const override { return std::to_string(value); };
	void setWithString(std::string str) override;
	
	//Static Functions : Cast and New
	static SFloat* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { value = cast(a)->value; };
	virtual void add(SType* a) override { value += cast(a)->value; };
	virtual void min(SType* a) override { value -= cast(a)->value; };
	virtual void mul(SType* a) override { value *= cast(a)->value; };
	virtual void div(SType* a) override { value /= cast(a)->value; };

	//Operators returning operation over object
	virtual SFloat* retAdd(SType* a) const override { return new SFloat(value + cast(a)->value); };
	virtual SFloat* retMin(SType* a) const override { return new SFloat(value - cast(a)->value); };
	virtual SFloat* retMul(SType* a) const override { return new SFloat(value * cast(a)->value); };
	virtual SFloat* retDiv(SType* a) const override { return new SFloat(value / cast(a)->value); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { return value == cast(a)->value; };
	virtual bool isSup(SType* a) const override { return value > cast(a)->value; };
	virtual bool isInf(SType* a) const override { return value < cast(a)->value; };
};

//Soyuz Boolean
class SBool : public SType
{
public:
	SBool(bool b) : SType(), value(b) { type = "boolean"; }
	~SBool() {};
	bool value;

	//Functions to convert to string and set with string
	std::string print(std::string options) const override { return "Value : " + std::to_string(value); };
	std::string toString(std::string options) const override { return std::to_string(value); };
	void setWithString(std::string str) override;
	
	//Static Functions : Cast and New
	static SBool* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { value = cast(a)->value; };
	virtual void add(SType* a) override { value += cast(a)->value; };
	virtual void min(SType* a) override { value -= cast(a)->value; };
	virtual void mul(SType* a) override { value *= cast(a)->value; };
	virtual void div(SType* a) override { value /= cast(a)->value; };

	//Operators returning operation over object
	virtual SBool* retAdd(SType* a) const override { return new SBool(value + cast(a)->value); };
	virtual SBool* retMin(SType* a) const override { return new SBool(value - cast(a)->value); };
	virtual SBool* retMul(SType* a) const override { return new SBool(value * cast(a)->value); };
	virtual SBool* retDiv(SType* a) const override { return new SBool(value / cast(a)->value); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { return value == cast(a)->value; };
	virtual bool isSup(SType* a) const override { return value > cast(a)->value; };
	virtual bool isInf(SType* a) const override { return value < cast(a)->value; };
};

//Soyuz String
class SText : public SType
{
public:
	SText(std::string s) : SType(), value(s) { type = "text"; }
	~SText() {};
	std::string value;

	//Functions to convert to string and set with string
	std::string print(std::string options) const override { return value; };
	std::string toString(std::string options) const override { return value; };
	void setWithString(std::string str) override;
	
	//Static Functions : Cast and New
	static SText* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { value = cast(a)->value; };
	virtual void add(SType* a) override { value += cast(a)->value; };

	//Operators returning operation over object
	virtual SText* retAdd(SType* a) const override { return new SText(value + cast(a)->value); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { return value == cast(a)->value; };
	virtual bool isSup(SType* a) const override { return value > cast(a)->value; };
	virtual bool isInf(SType* a) const override { return value < cast(a)->value; };
};

//Soyuz Pointer
class SPointer : public SType
{
public:
	SPointer(SType* s) : SType(), value(s) { type = "pointer"; }
	~SPointer() {};
	SType* value;

	//Functions to convert to string and set with string
	std::string print(std::string options) const override { if (value != nullptr) return value->print(options); else return "null pointer"; };
	std::string toString(std::string options) const override { if (value != nullptr) return value->toString(options); else return "null pointer"; };
	void setWithString(std::string str) override { if (value != nullptr) value->setWithString(str); };

	//Use
	void use(std::string options) { if (value != nullptr) value->use(options); };

	//Static Functions : Cast and New
	static SPointer* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { if (value != nullptr) value->set(a); };
	virtual void add(SType* a) override { if (value != nullptr) value->add(a); };
	virtual void min(SType* a) override { if (value != nullptr) value->min(a); };
	virtual void mul(SType* a) override { if (value != nullptr) value->mul(a); };
	virtual void div(SType* a) override { if (value != nullptr) value->div(a); };
	virtual void mod(SType* a) override { if (value != nullptr) value->mod(a); };

	//Operators returning operation over object
	virtual SPointer* retAdd(SType* a) const override { if (value != nullptr) return cast(value->retAdd(a)); return new SPointer(nullptr);};
	virtual SPointer* retMin(SType* a) const override { if (value != nullptr) return cast(value->retMin(a)); return new SPointer(nullptr);};
	virtual SPointer* retMul(SType* a) const override { if (value != nullptr) return cast(value->retMul(a)); return new SPointer(nullptr);};
	virtual SPointer* retDiv(SType* a) const override { if (value != nullptr) return cast(value->retDiv(a)); return new SPointer(nullptr);};
	virtual SPointer* retMod(SType* a) const override { if (value != nullptr) return cast(value->retMod(a)); return new SPointer(nullptr);};

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { if (value != nullptr)return value->isEqu(a); return false; };
	virtual bool isSup(SType* a) const override { if (value != nullptr)return value->isSup(a); return false; };
	virtual bool isInf(SType* a) const override { if (value != nullptr)return value->isInf(a); return false; };
};