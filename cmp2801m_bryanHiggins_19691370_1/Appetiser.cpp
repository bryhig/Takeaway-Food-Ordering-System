#include "Appetiser.h"
//Appetiser constructor, instantiates an Appetiser object when parameters are passed into it.
Appetiser::Appetiser(string name1, int calories1, double price1, bool shareable1, bool twoForOne1)
{
	name = name1;
	calories = calories1;
	price = price1;
	shareable = shareable1;
	twoForOne = twoForOne1;
}

//Creates a string to represent an Appetiser object.
string Appetiser::toString()
{
	//Variables created, will all be combined to create one final string.
	string finalString;
	string twoForOneString;
	string shareableString;
	string caloriesString = to_string(calories) + " calories";
	string priceString = "\x9c" + to_string(price);

	//If the Appetiser object is eligable for a 2-4-1 discount, twoForOneString is given a value.
	if (twoForOne == true)
	{
		twoForOneString = "(2-4-1)";
	}
	//If the Appetiser object is shareable, shareableString is given a value.
	if (shareable == true)
	{
		shareableString = "(Shareable)";
	}

	//Default final string is created with all Appetiser attributes included.
	finalString = name + ", " + caloriesString + ", " + priceString.substr(0, 5) + ", " + twoForOneString + ", " + shareableString + "\n";

	//Overwrites finalString if the Appetiser is eligable for 2-4-1 discount, but its not shareable.
	if (twoForOne == true && shareable == false)
	{
		finalString = name + ", " + caloriesString + ", " + priceString.substr(0, 5) + ", " + twoForOneString + "\n";
	}
	//Overwrites finalString if the Appetiser is shareable, but doesnt have a 2-4-1 discount.
	else if (twoForOne == false && shareable == true)
	{
		finalString = name + ", " + caloriesString + ", " + priceString.substr(0, 5) + ", " + shareableString + "\n";
	}
	//Overwrites finalString the Appetiser is neither shareable or eligable for 2-4-1, 
	else if (twoForOne == false && shareable == false) 
	{
		finalString = name + ", " + caloriesString + ", " + priceString.substr(0, 5) + ", " + "\n";
	}
	//If the Appetiser meets none of the above conditions, it will keep the default final string with all atributes included.
	else
	{
		finalString = finalString;
	}

	//The final string is returned from the function.
	return finalString;
}

