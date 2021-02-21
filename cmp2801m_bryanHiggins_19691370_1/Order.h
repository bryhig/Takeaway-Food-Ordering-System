#pragma once
#include "ItemList.h"
//Derives from ItemList.
class Order : public ItemList
{
private:
	//Derived class specific attribute declared.
	double total{ 0 };
public:
	//Functions declared.
	double calculateTotal();
	double calculateDiscount();
	void printReceipt(string receipt);
	string toString();
	void add(Item* choice);
	void remove(int index);
	int checkout();
	bool isChoiceOkay(int index);
	
};

