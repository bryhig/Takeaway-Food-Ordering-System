#pragma once
#include "Item.h"
//Derives from Item.
class Appetiser : public Item
{
private:
	//Derived class specific attributes declared. Private for encapsulation.
	bool shareable;
	bool twoForOne;
public:
	//Constructor and parameters declared.
	Appetiser(string name1, int calories1, double price1, bool sharable1, bool twoForOne1);
	//toString() function declared.
	string toString();
};

