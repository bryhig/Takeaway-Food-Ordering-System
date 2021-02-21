#pragma once
#include "Item.h"
//Derives from Item.
class MainCourse : public Item
{
public:
	//Constructor and its parameters are declared.
	MainCourse(string name1, int calories1, double price1);
	string toString();
};

