#pragma once

#include "core/SType.h"
#pragma message ("type/Matrix Types are defined")

//Soyuz Mat4
class SMat4 : public SType
{
public:
	SMat4(glm::mat4 v) : SType(), value(v) { type = "mat4"; }
	~SMat4() {};
	glm::mat4 value;

	//To String and Set With String
	std::string toString(std::string options) const override;
	std::string print(std::string options) const override;
	void setWithString(std::string str) override;

	//Static Functions : Cast and New
	static SMat4* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { value = cast(a)->value; };
	virtual void add(SType* a) override { value += cast(a)->value; };
	virtual void min(SType* a) override { value -= cast(a)->value; };
	virtual void mul(SType* a) override { value *= cast(a)->value; };
	virtual void div(SType* a) override { value /= cast(a)->value; };

	//Operators returning operation over object
	virtual SMat4* retAdd(SType* a) const override { return new SMat4(value + cast(a)->value); };
	virtual SMat4* retMin(SType* a) const override { return new SMat4(value - cast(a)->value); };
	virtual SMat4* retMul(SType* a) const override { return new SMat4(value * cast(a)->value); };
	virtual SMat4* retDiv(SType* a) const override { return new SMat4(value / cast(a)->value); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { return value == cast(a)->value; };
};

//Soyuz Mat3
class SMat3 : public SType
{
public:
	SMat3(glm::mat3 v) : SType(), value(v) { type = "mat3"; }
	~SMat3() {};
	glm::mat3 value;

	//To String and Set With String
	std::string toString(std::string options) const override;
	std::string print(std::string options) const override;
	void setWithString(std::string str) override;

	//Static Functions : Cast and New
	static SMat3* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { value = cast(a)->value; };
	virtual void add(SType* a) override { value += cast(a)->value; };
	virtual void min(SType* a) override { value -= cast(a)->value; };
	virtual void mul(SType* a) override { value *= cast(a)->value; };
	virtual void div(SType* a) override { value /= cast(a)->value; };

	//Operators returning operation over object
	virtual SMat3* retAdd(SType* a) const override { return new SMat3(value + cast(a)->value); };
	virtual SMat3* retMin(SType* a) const override { return new SMat3(value - cast(a)->value); };
	virtual SMat3* retMul(SType* a) const override { return new SMat3(value * cast(a)->value); };
	virtual SMat3* retDiv(SType* a) const override { return new SMat3(value / cast(a)->value); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { return value == cast(a)->value; };
};

//Soyuz Mat2
class SMat2 : public SType
{
public:
	SMat2(glm::mat2 v) : SType(), value(v) { type = "mat2"; }
	~SMat2() {};
	glm::mat2 value;

	//To String and Set With String
	std::string toString(std::string options) const override;
	std::string print(std::string options) const override;
	void setWithString(std::string str) override;

	//Static Functions : Cast and New
	static SMat2* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { value = cast(a)->value; };
	virtual void add(SType* a) override { value += cast(a)->value; };
	virtual void min(SType* a) override { value -= cast(a)->value; };
	virtual void mul(SType* a) override { value *= cast(a)->value; };
	virtual void div(SType* a) override { value /= cast(a)->value; };

	//Operators returning operation over object
	virtual SMat2* retAdd(SType* a) const override { return new SMat2(value + cast(a)->value); };
	virtual SMat2* retMin(SType* a) const override { return new SMat2(value - cast(a)->value); };
	virtual SMat2* retMul(SType* a) const override { return new SMat2(value * cast(a)->value); };
	virtual SMat2* retDiv(SType* a) const override { return new SMat2(value / cast(a)->value); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { return value == cast(a)->value; };
};
