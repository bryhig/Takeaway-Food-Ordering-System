#include "Beverage.h"
//Beverage constructor, instantiates a Beverage object when parameters passed into it.
Beverage::Beverage(string name1, int calories1, double price1, double abv1, int volume1)
{
	name = name1;
	calories = calories1;
	price = price1;
	abv = abv1;
	volume = volume1;
}

//Checks to see if the Beverage object is alcoholic.
bool Beverage::isAlcoholic()
{
	//If the abv is greater than 0, then the object is alcoholic.
	if (abv > 0)
	{
		return true;
	}
	//If it isnt, its not alcoholic.
	else
	{
		return false;
	}
}

//Creates a string that represents a Beverage object and its attributes.
string Beverage::toString()
{
	//Variables created representing different atributes of the object.
	string caloriesString = to_string(calories) + " calories";
	string priceString = "\x9c" + to_string(price);
	string volumeString = to_string(volume) + "ml";
	string abvString1 = to_string(abv).substr(0, 4);
	string abvString2 = abvString1 + "% abv";
	//Two final strings initialised, the first is for aloholic beverages, the second is for non-alcoholic. 
	string finalString = name + ", " + caloriesString + ", " + priceString.substr(0, 5) + ", "  "(" + volumeString + ", " + abvString2 + ")" + "\n";
	string finalString2 = name + ", " + caloriesString + ", " + priceString.substr(0, 5) + ", " + "(" + volumeString + ")" + "\n";
	
	//The isAlcoholic() function is called, if the Beverage isnt alcoholic, then the final string for non-alcoholic beverages is returned (doesnt include abv).
	if (isAlcoholic() == false)
	{
		return finalString2;
	}

	//If the Beverage object is alcoholic, then the final string for alcoholic drinks will be returned (includes the abv).
	return finalString;
}
