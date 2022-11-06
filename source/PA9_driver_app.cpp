//------------------------------------------------------------------------------
// app.cpp : LinkedList class driver
//------------------------------------------------------------------------------
#include <iostream>

#include "LinkedList.h"

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cout;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr bool ADD = false;
constexpr bool INS = !ADD;

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
const int g_testNew[] = {
	73, // case 1: new data node is first list node
	71, // case 2: new data node becomes new head of list
	72, // case 4: new data node inserted between nodes
	75, // case 3: new data node added after tail, becomes new tail of list
	74, // case 4: new data node inserted between nodes
	75, // case 3: new data node added after tail, becomes new tail of list
};

const int g_testDelete[] = {
	73,   // case 1: delete node in the middle of the list
	71,   // case 2: delete node at list head
	75,   // case 3: delete node at list tail
	75,   // delete node at list tail again
	100,  // case 4: delete node that's not in the list
};

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
template <typename T>
void testAdd(LinkedList<T>& myList);
template <typename T>
void testInsert(LinkedList<T>& myList);
template <typename T>
void testDelete(LinkedList<T>& myList);

// delete node, show remaining list data
template <typename T>
inline bool _zapNshow(LinkedList<T>& list, T data);

// insert (true) or add (false) new node and show list data
template <typename T>
inline void _newNshow(LinkedList<T>& list, T data, bool insert = INS);

template <typename T>
inline void displayNodeData(LinkedList<T>& dataList);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

//------------------------------------------------------------------------------
// test int list
//------------------------------------------------------------------------------
	LinkedList<int> myIntList;
	cout << "\nTEST INT LIST\n\n";

	//--------------------------------------------------------------------------
	// add some list items, on add each one becomes the new list head
	//--------------------------------------------------------------------------
	//testAdd(myIntList);

	//--------------------------------------------------------------------------
	// insert some list items in ascending sort order
	//--------------------------------------------------------------------------
	testInsert(myIntList);

	//--------------------------------------------------------------------------
	// delete list items
	//--------------------------------------------------------------------------
	testDelete(myIntList);

//------------------------------------------------------------------------------
// test char list
//------------------------------------------------------------------------------
	LinkedList<char> myCharList;
	cout << "\nTEST CHAR LIST\n\n";

	//--------------------------------------------------------------------------
	// add some list items, on add each one becomes the new list head
	//--------------------------------------------------------------------------
	//testAdd(myCharList);

	//--------------------------------------------------------------------------
	// insert some list items in ascending sort order
	//--------------------------------------------------------------------------
	testInsert(myCharList);

	//--------------------------------------------------------------------------
	// delete list items
	//--------------------------------------------------------------------------
	testDelete(myCharList);

	// END TEST release all node memory
	myIntList.makeEmpty();

	// good c++itizen
	return 0;
}

//------------------------------------------------------------------------------
// exercise addNode()
//
// add some list items, on add each one becomes the new list head
//------------------------------------------------------------------------------
template <typename T>
void testAdd(LinkedList<T>& list) {

	for (T data : g_testNew) {
		_newNshow(list, data, ADD);
	}
}

//------------------------------------------------------------------------------
// exercise insertNode()
//
// check all four cases insertNode() must handle
// for a thorough list test check all cases
// several times in different orders
//
//	case 1: new data node is first list node
//	case 2: new data node becomes new head of list
//	case 3: new data node added after tail, becomes new tail of list
//	case 4: new data node inserted between nodes
//------------------------------------------------------------------------------
template <typename T>
void testInsert(LinkedList<T>& list) {

	for (T data : g_testNew) {
		_newNshow(list, data, INS);
	}
}

//------------------------------------------------------------------------------
// exercise deleteNode()
//
// check all four cases deleteNode() must handle
// for a thorough list test check all cases
// several times in different orders
//------------------------------------------------------------------------------
template <typename T>
void testDelete(LinkedList<T>& list) {

	// for testing deleteNode() return value
	bool deleted;

	for (T data : g_testDelete) {
		deleted = _zapNshow(list, data);
	}
}

//------------------------------------------------------------------------------
// delete node, show remaining list data
//------------------------------------------------------------------------------
template <typename T>
inline bool _zapNshow(LinkedList<T>& list, T data) {

	cout << "\ndeleting " << data << "...";

	bool deleted = list.deleteNode(data);

	if (!deleted) {
		cout << "not found";
	}
	else {
		cout << "ok";
	}

	displayNodeData(list);

	return deleted;
}

//------------------------------------------------------------------------------
// add or insert node then show list data
// 
// inserts node when insert is true, adds node otherwise
//------------------------------------------------------------------------------
template <typename T>
inline void _newNshow(LinkedList<T>& list, T data, bool insert) {

	if (insert) {
		cout << "\ninserting sorted " << data;
		list.insertNode(data);
	}
	else {
		cout << "\nadding unsorted " << data;
		list.addNode(data);
	}

	displayNodeData(list);
}

//------------------------------------------------------------------------------
// display each data item in the passed list
//------------------------------------------------------------------------------
template <typename T>
inline void displayNodeData(LinkedList<T>& dataList) {
	
	//--------------------------------------------------------------------------
	// _always check list status before walking the list!
	//--------------------------------------------------------------------------
	if (dataList.isEmpty()) {
		cout << "empty list\n";
		return;
	}

	// reset list position pointer to list head
	//-----------------------------------------------------------------------------
	// You have to do this because 
	//		a) each .putItem() call changes myIntList's Position pointer, and
	//		b) .getCurrentNodeData() uses that same Position pointer.
	// 
	// When reusing someone else's class, you must understand it how to use
	// the public methods. Ideally class methods are declared in a way that
	// makes it pretty obvious how to use the class. Here it's not obvious,
	// you have to look closely at LinkedList class code to effectively use
	// its methods.
	// 
	// This LinkedList class offers easy list traversal with gotoHead() and
	// gotoNext(), plus it gives you a bookmark pointer to the current node.
	// The Position pointer is that bookmark.
	// 
	// Bottom line: when you post code to GitHub, make it easy to use.
	//		- briefly explain each function in its comment header, then
	//		- copy/paste those into README.MD file bullet items.
	// 
	//--------------------------------------------------------------------------
	// reset list position pointer to list head
	dataList.gotoHead();
	
	//cout << "\nat list head";
	// walk the list, get each node data item, display it
	do {
		// "bucket" for receiving node data in reference parameter
		T dataBucket;
		if (dataList.getCurrentNodeData(dataBucket)) {
			cout << '\n' << dataBucket;
		}
		else {
			//cout << "\nat list tail\n";
			cout << '\n';
		}
	} while (dataList.gotoNext());
	//-----------------------------------------------------------------------------
	// gotoNext() advances the Position pointer to the next list item
	//-----------------------------------------------------------------------------
}