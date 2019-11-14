#pragma once
#pragma message ("type/DataStructureType are defined")

#include "core/SType.h"

//Node
struct Node
{
	Node*	before;
	SType*	self;
	Node*	after;
};

//List Class
class SList
{
public:

	//Constructor / Destructor
	SList();
	~SList();

	//Node at position
	Node* nodeAt(unsigned int pos) const;

	//Value at position
	SType* valueAt(unsigned int pos) const;

	//Push Back
	void push_back(SType* obj);

	//Pop Back
	void pop_back();

	//Insert before the elements at given position
	void insert(unsigned int pos, SType* obj);

	//Insert a list
	void insert(unsigned int pos, SList* list);

	//Remove at position
	void remove(unsigned int pos);

private:

	//First Node
	Node* m_first;

	//Last Node
	Node* m_last;
};