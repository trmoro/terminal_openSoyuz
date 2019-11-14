#pragma once

#include "core/SType.h"
#pragma message ("type/Vertex Type is defined")

#include "type/VecType.h"

class Vertex : public SType
{
public:
	Vertex(SVec3* position, SVec3* normal, SVec2* texture_uv);
	Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 uv);

	SVec3* m_position;
	SVec3* m_normal;
	SVec2* m_texture_uv;

	//To String and Set With String
	std::string toString(std::string options) const override;
	void setWithString(std::string str) override;

	//Use
	void use(std::string options) override;

	//Static Functions : Cast and New
	static Vertex* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Operators modifying object
	virtual void set(SType* a) override { Vertex* v = cast(a); m_position = v->m_position; m_normal = v->m_normal; m_texture_uv = v->m_texture_uv; };
	virtual void add(SType* a) override { Vertex* v = cast(a); m_position->add(v->m_position); m_normal->add(v->m_normal); m_texture_uv->add(v->m_texture_uv); };
	virtual void min(SType* a) override { Vertex* v = cast(a); m_position->min(v->m_position); m_normal->min(v->m_normal); m_texture_uv->min(v->m_texture_uv); };
	virtual void mul(SType* a) override { Vertex* v = cast(a); m_position->mul(v->m_position); m_normal->mul(v->m_normal); m_texture_uv->mul(v->m_texture_uv); };
	virtual void div(SType* a) override { Vertex* v = cast(a); m_position->div(v->m_position); m_normal->div(v->m_normal); m_texture_uv->div(v->m_texture_uv); };

	//Operators returning operation over object
	virtual Vertex* retAdd(SType* a) const override { Vertex* v = cast(a);  return new Vertex(m_position->retAdd(v->m_position), m_normal->retAdd(v->m_normal), m_texture_uv->retAdd(v->m_texture_uv) ); };
	virtual Vertex* retMin(SType* a) const override { Vertex* v = cast(a);  return new Vertex(m_position->retMin(v->m_position), m_normal->retMin(v->m_normal), m_texture_uv->retMin(v->m_texture_uv)); };
	virtual Vertex* retMul(SType* a) const override { Vertex* v = cast(a);  return new Vertex(m_position->retMul(v->m_position), m_normal->retMul(v->m_normal), m_texture_uv->retMul(v->m_texture_uv)); };
	virtual Vertex* retDiv(SType* a) const override { Vertex* v = cast(a);  return new Vertex(m_position->retDiv(v->m_position), m_normal->retDiv(v->m_normal), m_texture_uv->retDiv(v->m_texture_uv)); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const override { Vertex* v = cast(a); return (m_position->isEqu(v->m_position) && m_normal->isEqu(v->m_normal) && m_texture_uv->isEqu(v->m_texture_uv) ); };
private:
	void renameChildren();
};