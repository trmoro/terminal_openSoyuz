#pragma once

#include "core/SType.h"
#pragma message ("type/Vector Types are defined")

//Soyuz Vec4
class SVec4 : public SType
{
public:
	SVec4(glm::vec4 v) : SType(), value(v) { type = "vec4"; }
	~SVec4() {};
	glm::vec4 value;

	//To String and Set With String
	std::string toString(std::string options) const override;
	std::string print(std::string options) const override;
	void setWithString(std::string str) override;

	//Static Functions : Cast and New
	static SVec4* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { value = cast(a)->value; };
	virtual void add(SType* a) override { value += cast(a)->value; };
	virtual void min(SType* a) override { value -= cast(a)->value; };
	virtual void mul(SType* a) override { value *= cast(a)->value; };
	virtual void div(SType* a) override { value /= cast(a)->value; };

	//Operators returning operation over object
	virtual SVec4* retAdd(SType* a) const override { return new SVec4(value + cast(a)->value); };
	virtual SVec4* retMin(SType* a) const override { return new SVec4(value - cast(a)->value); };
	virtual SVec4* retMul(SType* a) const override { return new SVec4(value * cast(a)->value); };
	virtual SVec4* retDiv(SType* a) const override { return new SVec4(value / cast(a)->value); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { return value == cast(a)->value; };
};

//Soyuz Vec3
class SVec3 : public SType
{
public:
	SVec3(glm::vec3 v) : SType(), value(v) { type = "vec3"; }
	~SVec3() {};
	glm::vec3 value;

	//To String and Set With String
	std::string toString(std::string options) const override;
	std::string print(std::string options) const override;
	void setWithString(std::string str) override;

	//Static Functions : Cast and New
	static SVec3* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { value = cast(a)->value; };
	virtual void add(SType* a) override { value += cast(a)->value; };
	virtual void min(SType* a) override { value -= cast(a)->value; };
	virtual void mul(SType* a) override { value *= cast(a)->value; };
	virtual void div(SType* a) override { value /= cast(a)->value; };

	//Operators returning operation over object
	virtual SVec3* retAdd(SType* a) const override { return new SVec3(value + cast(a)->value); };
	virtual SVec3* retMin(SType* a) const override { return new SVec3(value - cast(a)->value); };
	virtual SVec3* retMul(SType* a) const override { return new SVec3(value * cast(a)->value); };
	virtual SVec3* retDiv(SType* a) const override { return new SVec3(value / cast(a)->value); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { return value == cast(a)->value; };
};

//Soyuz Vec2
class SVec2 : public SType
{
public:
	SVec2(glm::vec2 v) : SType(), value(v) { type = "vec2"; }
	~SVec2() {};
	glm::vec2 value;

	//To String and Set With String
	std::string toString(std::string options) const override;
	std::string print(std::string options) const override;
	void setWithString(std::string str) override;

	//Static Functions : Cast and New
	static SVec2* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { value = cast(a)->value; };
	virtual void add(SType* a) override { value += cast(a)->value; };
	virtual void min(SType* a) override { value -= cast(a)->value; };
	virtual void mul(SType* a) override { value *= cast(a)->value; };
	virtual void div(SType* a) override { value /= cast(a)->value; };

	//Operators returning operation over object
	virtual SVec2* retAdd(SType* a) const override { return new SVec2(value + cast(a)->value); };
	virtual SVec2* retMin(SType* a) const override { return new SVec2(value - cast(a)->value); };
	virtual SVec2* retMul(SType* a) const override { return new SVec2(value * cast(a)->value); };
	virtual SVec2* retDiv(SType* a) const override { return new SVec2(value / cast(a)->value); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { return value == cast(a)->value; };
};
