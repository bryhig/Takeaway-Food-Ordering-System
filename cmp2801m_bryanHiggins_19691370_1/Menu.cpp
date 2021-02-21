#include "Menu.h"
#include "Appetiser.h"
#include "MainCourse.h"
#include "Beverage.h"
#include <fstream>
#include <vector>
#include <iostream>

Menu::Menu(string file)
{
	//Creates a file object, and opens the file.
	ifstream myFile;
	myFile.open(file);
	
	//Creating variables to store .csv file data in, these will later be passed into constructors to create items.
	string type;
	string name;
	string price;
	string calories;
	string shareable;
	string TwoforOne;
	string volume;
	string abv;
	
	//Will be given values when Appetiser objects are instantiated.
	bool TwoForOneBool;
	bool shareableBool;

	//This reads through the .csv file cell by cell left to right. It stores the data held within each cell in its corresponding variable.
	//The loop goes back to the begining once each row has been read.
	//Type = "a", "m" or "b" used to decide wether to instantiate an Appetiser, MainCourse or Beverage object.
	while (getline(myFile, type, ',')) {
		getline(myFile, name, ',');
		getline(myFile, price, ',');
		//Converting price to double, so that it can be passed into constructors.
		double pricedoub = stod(price);
		getline(myFile, calories, ',');
		int caloriesint = stoi(calories);
		getline(myFile, shareable, ',');
		getline(myFile, TwoforOne, ',');
		getline(myFile, volume, ',');
		getline(myFile, abv);

		//If the items type is "a",  an Appetiser object is prepared to be instantiated.
		if (type == "a") {
			//Boolean values to represent whether the Appetiser is eligable for 2-4-1 discount, and whether the item is shareable are created.
			if (TwoforOne == "y")
			{
				TwoForOneBool = true;
			}
			else
			{
				TwoForOneBool = false;
			}
			if (shareable == "y")
			{
				shareableBool = true;
			}
			else
			{
				shareableBool = false;
			}

			//A new Appetiser object is instantiated as a pointer value, and pushed back into the Menu's "items" vector.
			//The data read from the menu.csv file is passed into the constructor.
			Appetiser* temp = new Appetiser(name, caloriesint, pricedoub, shareableBool, TwoForOneBool);
			items.push_back(temp);
		}
		//If the type is "m", a MainCourse object is instantiated.
		else if (type == "m") {

			//The data read from the menu.csv file is passed into the constructor, and a new pointer MainCourse object is instantiated and pushed back into the Menus "items" vector.
			MainCourse* temp = new MainCourse(name, caloriesint, pricedoub);
			items.push_back(temp);
		}
		//If the type is "b", a Beverage object is instantiated.
		else if (type == "b") {
			//The volume and abv data read from menu.csv is converted to integer and double, so that it can be passed into the constructor.
			int volumeint = stoi(volume);
			double abvdoub = stod(abv);
			//The data read from menu.csv is passed into the constructor, and a new pointer Beverage object is instantiated and pushed back into the Menu's "items" vector.
			Beverage* temp = new Beverage(name, caloriesint, pricedoub, abvdoub, volumeint);
			items.push_back(temp);
		}
		//If the menu.csv file was altered, and an invalid type was detected, the user will be informed.
		else
		{
			cout << "ERROR: INVALID ITEM TYPE DETECTED IN MENU" << endl;
		}
	}

	//menu.csv is closed.
	myFile.close();

}
//Creates a string to represent the menu, so that it can be readed.
string Menu::toString()
{
	cout << "\n";
	//A final string is initialized, all of the items will be added to this string.
	string finalString;
	//For every Item object contained within the Menu's "items" vector, each items individual toString() function will be called.
	for (int i = 0; i < items.size(); ++i)
	{
		//Different titles are displayed based on how far through the menu the loop is.
		if (i == 0) 
		{
			finalString = "=============BRYANS TAKEAWAY MENU=============\n";
			finalString = finalString + "----------------APPETISERS----------------\n";
		}
		//An item number for each item is created, and each item within the vectors toString() function is called.
		//The item number and the individual items string are then added to the final string.
		string itemNumber = "(" + to_string(i + 1) + ") ";
		finalString = finalString + itemNumber + items[i]->toString();

		if (i == 2) 
		{
			finalString = finalString + "---------------MAIN COURSES---------------\n";
		}
		if (i == 6) 
		{
			finalString = finalString + "----------------BEVERAGES----------------\n";
		}
	}
	finalString = finalString + "\n";
	//The final string is returned, and a readable string representing the menu has been produced.
	return finalString;

}

//This function checks to see if the users choice was valid (e.g. if the item selected is actually on the menu).
//The int index passed into the function represents an items menu number (e.g. 6 == Burger), which will be passed into the add/remove functions.
bool Menu::isChoiceOkay(int index) 
{
	//If the user enters an item number that is out of the bounds of the menus size is selected by the user, then there choice was invalid.
	//(e.g. add 19)
	if (index > items.size() || index <= 0) 
	{
		return false;
	}
	//If it is in the bounds of the menus size, then the choice was valid.
	else 
	{
		return true;
	}
}
//Initializes an Item pointer variable that will either be added or removed from the Order classes "items" vector.
//The int index passed into the function represents the chosen items menu number. 
Item* Menu::makeChoice(int index)
{
		Item* choice = items[index - 1];
		return choice;
}
//The Menu destructor.
Menu::~Menu() 
{
	//Deletes every pointer object contained within the Menu's "items" vector to prevent memory leaks.
	for (int i = 0; i < items.size(); ++i) 
	{
		delete items[i];
	}
	items.clear();
}



