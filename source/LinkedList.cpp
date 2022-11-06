//------------------------------------------------------------------------------
// LinkedList.cpp : class definition
// 
// Author: unknown book example, unknown author
// 
// This code is intended as an example for students in my classes.
//------------------------------------------------------------------------------
#include "LinkedList.h"

//------------------------------------------------------------------------------
// constructor
//------------------------------------------------------------------------------
LinkedList::LinkedList() {
	head = nullptr;

	// set Position pointer to list head
	gotoHead();
}

//------------------------------------------------------------------------------
// destructor
//------------------------------------------------------------------------------
LinkedList::~LinkedList() { makeEmpty(); }

//------------------------------------------------------------------------------
// new item becomes list head
//------------------------------------------------------------------------------
void LinkedList::addNode(T data) {

	Node<T>* pNode = new Node<T>(data);

	pNode->next = head;
	head = pNode;

	// before first item is added Position is nullptr
	if (Position == nullptr)
		gotoHead();
}

//------------------------------------------------------------------------------
// insert list node containing passed data value
// 
// handles 4 cases:
//		1. new data node is first list node
//		2. new data node becomes new head of list
//		3. new data node added after tail, becomes new tail of list
//		4. new data node inserted between nodes
// 
// inserts duplicate data _before existing node with same data value
// 
// updates Position pointer to new node
// 
//------------------------------------------------------------------------------
void LinkedList::insertNode(T data) {

	Node<T>* pNode = new Node<T>(data);

	// case 1: new data node is first list node
	if (head == nullptr) {
		head = pNode;
		gotoHead();
		return;
	}

	//-----------------------------------------------------------------------------
	// working pointers preserve head pointer, traverse the list
	//		- p starts off pointing to list head, follows each node's next pointer
	//		- pPrev starts off nullptr, follows one node behind p
	//-----------------------------------------------------------------------------
	Node<T>* p = head;
	Node<T>* pPrev = nullptr;

	//-----------------------------------------------------------------------------
	// traverse the list with a while loop
	// 
	// the values of p and pPrev after this while loop
	// determine which case passed data presents
	//-----------------------------------------------------------------------------

	while (p && p->data < data) {
		pPrev = p;
		p = p->next;
	}
	
	// case 2: new data node becomes new head of list
	if (pPrev == nullptr) {
		pNode->next = head;
		head = pNode;

		// update Position pointer
		gotoHead();
		return;
	}

	//-----------------------------------------------------------------------------
	// case 3: new data node added after tail, becomes new tail of list
	// and
	// case	4. new data node inserted between nodes
	//-----------------------------------------------------------------------------
	pPrev->next = pNode;
	pNode->next = p;

	// update internal list pointers
	Position = pNode;
	_prevPosition = pPrev;
}

//------------------------------------------------------------------------------
// delete list node containing passed data value
//------------------------------------------------------------------------------
bool LinkedList::deleteNode(T matchData) {

	_setPosition(matchData);

	// data not found
	if (Position == nullptr)
		return false;

	// data found, Position points to the containing node
	Node<T>* pNode = Position;

	// data at list end
	if (pNode->next == nullptr) {
		_prevPosition->next = nullptr;
		Position = _prevPosition;
	}
	// nodes before and after data
	else if (_prevPosition != nullptr) {
		_prevPosition->next = pNode->next;
		Position = _prevPosition->next;
	}
	// data at list head
	else {
		head = pNode->next;
		gotoHead();
	}

	// release node memory
	delete pNode;

	return true;
}

//------------------------------------------------------------------------------
// reset Position to list head
//------------------------------------------------------------------------------
void LinkedList::gotoHead() {
	Position = head;
	_prevPosition = nullptr;
}

//------------------------------------------------------------------------------
// advances Position pointer to the next node on the list, if possible
// 
// returns 
//		- new Position, when Position did in fact advance
//		- nullptr, when Position is at list end and cannot advance
//------------------------------------------------------------------------------
bool LinkedList::gotoNext() {

	if (Position != nullptr) {
		// advance
		Position = Position->next;
		return true;
	}

	// can't advance when Position is 0
	return false;
}

//------------------------------------------------------------------------------
// return the list item pointed to by Position in reference param
//------------------------------------------------------------------------------
bool LinkedList::getCurrentNodeData(T& fillWithData) {

	if (Position != nullptr) {
		fillWithData = Position->data;
		return true;
	}

	return false;
}

//------------------------------------------------------------------------------
// sets Position pointer to node containing passed data value (private)
//------------------------------------------------------------------------------
void LinkedList::_setPosition(T matchData) {

	gotoHead();

	bool found = false;
	while (Position != nullptr && !found) {

		if (Position->data == matchData) {
			found = true;
			break;
		}

		// keep previous position for easy deleteNode
		_prevPosition = Position;

		// advance Position to next node on the list
		gotoNext();
	}
}

//------------------------------------------------------------------------------
// returns true if list is empty, false otherwise
//------------------------------------------------------------------------------
bool LinkedList::isEmpty() {

	return (head == nullptr) ? true : false;
}

//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------
void LinkedList::makeEmpty() {

	if (isEmpty())
		return;

	gotoHead();

	while (Position != nullptr) {
		// save each Position value
		Node* pNode = Position;

		// then gotoNext() advances Position to next node on the list
		gotoNext();

		// now our Position is the next node, we can
		// delete previous Position's memory
		// the memory deleted is every Node instance
		delete pNode;
	}

	head = nullptr;
	Position = nullptr;
}
