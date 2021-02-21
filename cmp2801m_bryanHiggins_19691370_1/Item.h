#pragma once
#include <string>
using namespace std;
//Abstract class.
class Item
{
protected:
	//Attributes declared.
	int calories{ 0 };
	double price{ 0 };
	string name;
public:
	//Pure virtual toString() function declared. 
	virtual string toString() = 0;
	//Other functions declared.
	string getName();
	double getPrice();
};

