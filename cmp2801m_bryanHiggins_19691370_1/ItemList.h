#pragma once
#include "Item.h"
#include <vector>
#include <iostream>
using namespace std;
//Abstract class.
class ItemList
{
protected:
	//Attribute declared.
	vector<Item*> items;
public:
	//Pure virtual toString() function declared. Will never be called from this class.
	virtual string toString() = 0;
};

