#pragma once
#pragma message ("core/Process is defined")

#include <iostream>
#include <map>

#include "core/SType.h"
#include "core/IO.h"

#include "type/VecType.h"

class Process : public SType
{
public:

	//Constructor and Destructor
	Process();
	~Process();

	//Init
	virtual void init();
	bool isInit() const;

	//Update and Render
	void update() override;
	void render() override;

	//Query Objects
	std::map<std::string, SType*> query(std::string query) const;

	//Set and Get IO
	void	setIO(IO* io);
	IO*		getIO() const;

	//Get Object
	std::vector<SType*> getObjects() const;

	//Add Objects
	void add(SType* a) override;

	//To String and Set With String (Parent Function)
	std::string print(std::string options) const override;
	std::string toString(std::string options) const override;
	void setWithString(std::string str) override;

	//Static Function : New
	static Process* newType(std::vector<std::string> args);

protected:

	//IO
	IO* m_io;

	//Is Init
	bool m_isInit;

private:

	//Clear color
	SVec4* m_clearColor;

	//Object to store objects
	SType* m_objects;
};