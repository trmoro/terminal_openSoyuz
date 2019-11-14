#include "type/DataStructureType.h"
#include "..\..\include\type\DataStructureType.h"

//Constructor
SList::SList()
{
	m_first = nullptr;
	m_last	= nullptr;
}

//Destructor
SList::~SList()
{
}

//Node At
Node* SList::nodeAt(unsigned int pos) const
{
	//At least first element is set
	if (m_first != nullptr)
	{
		//Cursor
		unsigned int i = 0;

		//Return value
		Node* ret = m_first;

		//Increment cursor to the position and change return value
		while (i != pos)
		{
			if (ret->after != nullptr)
				ret = ret->after;

			i++;
		}

		//Return
		return ret;
	}
	//Else return null
	return nullptr;
}

//At
SType* SList::valueAt(unsigned int pos) const
{
	Node* n = nodeAt(pos);
	if (n != nullptr)
		return n->self;
	else
		return nullptr;
}

//Push Back
void SList::push_back(SType* obj)
{
	//First not set ?
	if (m_first == nullptr)
		m_first = new Node{ nullptr,obj,nullptr };
	//Last not set ?
	else if (m_last == nullptr)
	{
		m_last = new Node{ m_first,obj,nullptr };
		m_first->after = m_last;
	}
	//Insert after the end
	else
	{
		Node* n = new Node{ m_last,obj,nullptr };
		m_last->after = n;
		m_last = n;
	}
}

//Pop Back
void SList::pop_back()
{
	m_last = m_last->before;

	delete m_last->after;
	m_last->after = nullptr;
}

//Insert before the elements at given position
void SList::insert(unsigned int pos, SType* obj)
{
	//Get Node
	Node* n = nodeAt(pos);
	if (n != nullptr)
	{
		//Is first
		if (n == m_first)
		{
			m_first = new Node{ nullptr,obj,n };
			n->before = m_first;
		}
		//Other
		else
		{

		}
	}
}

//Insert a list
void SList::insert(unsigned int pos, SList* list)
{

}

//Remove at position
void SList::remove(unsigned int pos)
{

}