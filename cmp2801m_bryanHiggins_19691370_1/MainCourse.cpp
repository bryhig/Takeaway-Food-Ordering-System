#include "MainCourse.h"
//MainCourse constructor, instantiates a MainCourse object when parameters are passed into it.
MainCourse::MainCourse(string name1, int calories1, double price1)
{
	name = name1;
	calories = calories1;
	price = price1;
}
//Creates a string that represents a MainCourse object.
string MainCourse::toString()
{
	//Strings to represent a MainCourse objects attributes are initialized.
	string caloriesString = to_string(calories) + " calories";
	//"\x9c" represents a GBP sign.
	string priceString = "\x9c" + to_string(price);

	//Final string that contains all of the MainCourse attributes is initialized and returned.
	string finalString = name + ", " + caloriesString + ", " + priceString.substr(0, 5) + "\n";
	return finalString;

}

