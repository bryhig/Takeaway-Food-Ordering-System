#pragma once
#include "Item.h"
//Derives from Item.
class Beverage : public Item
{
private:
	//Derived class specific attributes declared. Private for encapsulation.
	double abv{ 0 };
	int volume{ 0 };
public:
	//Constructor and its parameters declared.
	Beverage(string name1, int calories1, double price1, double abv1, int volume1);
	//Other functions declared.
	bool isAlcoholic();
	string toString();
};

