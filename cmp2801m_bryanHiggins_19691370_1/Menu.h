#pragma once
#include "ItemList.h"
//Derives from ItemList.
class Menu : public ItemList
{
public:
	//Constructor and parameters declared.
	Menu(string file);
	//Other functions declared.
	string toString();
	bool isChoiceOkay(int index);
	Item* makeChoice(int index);
	//Destructor decalred.
	~Menu();
};

