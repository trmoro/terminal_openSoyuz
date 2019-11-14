#pragma once
#pragma message ("core/SType is defined")

#include <string>
#include <vector>

#include <iostream>
#include <algorithm>

#include "glm/glm.hpp"

class SType
{
public:

	//Constructor and Destructor
	SType();
	~SType();

	//Get/Set Parent
	SType* getParent() const;
	void setParent(SType* parent);

	//Get Children
	std::vector<SType*> getChildren() const;

	//Get Children Name/Type
	std::vector<std::string> getChildrenName() const;
	std::vector<std::string> getChildrenType() const;

	//Sort Children
	void sortChildren(std::string option);

	//PopBack Children
	void popBackChildren(unsigned int n);

	//Functions to convert to string and set with string
	virtual std::string print(std::string options) const;
	virtual std::string toString(std::string options) const;
	virtual void setWithString(std::string str);

	//Use inner functions
	virtual void use(std::string options);

	//Update and Render
	virtual void update();
	virtual void render();

	//Static Functions : Cast and New
	static SType* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Static Function to convert a string to a toString
	static std::string searchToString(std::string str, SType* from);

	//Operators modifying object
	virtual void set(SType* a) {};
	virtual void add(SType* a) {};
	virtual void min(SType* a) {};
	virtual void mul(SType* a) {};
	virtual void div(SType* a) {};
	virtual void mod(SType* a) {};

	//Operators returning operation over object
	virtual SType* retAdd(SType* a) const { return new SType(); };
	virtual SType* retMin(SType* a) const { return new SType(); };
	virtual SType* retMul(SType* a) const { return new SType(); };
	virtual SType* retDiv(SType* a) const { return new SType(); };
	virtual SType* retMod(SType* a) const { return new SType(); };

	//Boolean Base Tests
	virtual bool isEqu(SType* a) const { return false; };
	virtual bool isSup(SType* a) const { return false; };
	virtual bool isInf(SType* a) const { return false; };

	//Boolean Tests depending over Base Tests
	virtual bool isNotEqu(SType* a) const { return !isEqu(a); };
	virtual bool isSupEqu(SType* a) const { return isSup(a) || isEqu(a); };
	virtual bool isInfEqu(SType* a) const { return isInf(a) || isEqu(a); };

	//Get / Create Config
	SType*	getConfig() const;
	void	createConfig();
	bool	isConfigCreated() const;

	//Public variables
	std::string	name;
	std::string type;

private:

	//Sorting
	void sortABC();
	void sortType();


	SType* m_parent;
	std::vector<SType*> m_children;

	SType* m_config;
	bool m_isConfigCreated;
};