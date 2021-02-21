#include "Order.h"
#include <fstream>
//Adds an item to the order. The Item pointer choice passed into function is a pointer copied from the Menu.
void Order::add(Item* choice)
{
	//Chosen item is added to the order by being pushed back into the Order's "items" vector.
	items.push_back(choice);
	//The user is told which item they added to the order.
	string temp = choice->getName();
	cout << temp + " was added to the order!\n\n";
	//A new total for the order is calculated, as the item that has been added, price is added to the total.
	total = total + choice->getPrice();
}

//Removes an item from the order.
void Order::remove(int index) 
{
	//If the order is empty and the user tries to remove an item, they will be informed.
	if (items.empty() == true)
	{
		cout << "ERROR: The item you want to remove is not in the order. The order is currently empty.\n\n";
	}
	else 
	{
		//If the index entered is 1, the first item in the order is removed, the user is told, and the total is updated.
		if (index == 1) 
		{
			cout << items[index - 1]->getName() + " was removed from the order.\n\n";
			total = total - items[index - 1]->getPrice();
			items.erase(items.begin());
		}
		//Otherwise the element needing to be removed is the index entered - 1, the item is removed and the total is updated.
		else 
		{
			cout << items[index - 1]->getName() + " was removed from the order.\n\n";
			total = total - items[index - 1]->getPrice();
			items.erase(items.begin() + (index - 1));
		}
	}

}
//Creates a string to represent the order at Checkout.
string Order::toString()
{
	string finalString;
	cout << "\n========CHECKOUT========\n";
	//Iterates through the Order's "items" vector and calls every items toString() function, and adds the strings obtained from these to a final string.
	for (int i = 0; i < items.size(); ++i) 
	{
		finalString = finalString + "(" + to_string(i + 1) + ") " + items[i]->toString();
	}
	//Final string returned.
	return finalString;
}

//Calculates the total of the order, including any discounts that need to be subtracted from the total.
double Order::calculateTotal() 
{
	//The helper function calculateDiscount() is called to establish how much 2-4-1 discount the order is entitled too.
	double discount = calculateDiscount();
	//Discount is subtracted from the total.
	total = total - discount;

	//Total with discount subtracted is returned.
	return total;
}
//Called so that the user can see the items in their order, the total, any discounts applied. If the user confirms there order a receipt file is created.
int Order::checkout() 
{
	//If the user tries to checkout an empty order, they will be informed.
	if (items.empty() == true) 
	{
		cout << "ERROR: There is no order to checkout yet. Please add items to the order.\n\n";
		//0 is returned to indicate in main() that the user never confirmed there order.
		return 0;
    }
	//Else, the order will checkout.
	else 
	{
		//A string is initialized to be later added to the receipt file is created.
		string receipt;
		//Displays the order as a string by calling its toString() function.
		string checkoutString = toString();
		cout << checkoutString + "\n\n";
		//Calls calculateDiscount(), so that any discount can be displayed.
		double discount = calculateDiscount();
		string discountString;
		//Calls calculateTotal() so that the total can be displayed.
		double finalTotal = calculateTotal();
		string totalString;
		
		//The following conditions convert the discount to a string, and based on its value, cut down that strings length to remove any trailing 0's since it is a double.
		if (discount < 10) 
		{
			discountString = to_string(discount).substr(0, 4);
		}
		else if (discount >= 10) 
		{
			discountString = to_string(discount).substr(0, 5);
		}
		else
		{
			discountString = to_string(discount).substr(0, 6);
		}
		
		//The following conditions convert the total to a string, and based on its value, cut down that strings length to remove any trailing 0's since it is a double.
		if (finalTotal < 10) 
		{
			totalString = to_string(finalTotal).substr(0, 4);
		}
		else if (finalTotal >= 10) 
		{
			totalString = to_string(finalTotal).substr(0, 5);
		}
		else if (finalTotal >= 100) 
		{
			totalString = to_string(finalTotal).substr(0, 6);
		}
		else
		{
			totalString = to_string(finalTotal).substr(0, 7);
		}
		
		//If the discount is bigger than 0, then the discount subtracted from the total is displayed.
		//A string to represent the receipt is also created including any discounts.
		if (discount > 0)  
		{
			cout << "(2-4-1) discount applied, savings: \x9c" + discountString + "\n";
			receipt = "RECEIPT\n\n" + checkoutString + "\n\n" + "DISCOUNT: \x9c" + discountString + " has been taken off your total.\n" + "TOTAL: \x9c" + totalString;
		}
		//Else, a receipt string is created without any discount (as there aren't any).
		else 
		{
			receipt = "RECEIPT\n\n" + checkoutString + "\n\n" + "TOTAL: \x9c" + totalString;
		}
		//The total is displayed to the user.
		cout << "TOTAL: \x9c" + totalString + "\n\n";
		
		string userCommand;
		//While the user command is not equal to "n" or "N" the loop will run.
		while (userCommand != "n" || userCommand != "N") 
		{
			//User prompted to either confirm their order, or go back and modify it.
			cout << "Please enter 'y' to confirm your order, or 'n' to go back and modify it: ";
			//Whatever the user enters is retrived and stored in the userCommand variable.
			getline(cin, userCommand);
			//If the user enters "y" or "Y" their order is confirmed and a receipt is produced.
			if (userCommand == "y" || userCommand == "Y") 
			{
				//Calls printReceipt() function and passes in the receipt string variable created earlier.
				printReceipt(receipt);
				cout << "Order confirmed! enjoy your food!\n";
				//Returns 1 to indicate in main() that the user has confirmed their order.
				return 1;
			}
			//If the user enters "n" or "N", the function returns 0 to indicate that the user would like to go back and modify it.
			else if (userCommand == "n" || userCommand == "N") 
			{
				cout << "\n";
				return 0;
			}
			//Else, the user must have entered an invalid command, they are promted to enter a vlaid command.
			else 
			{
				cout << "ERROR: Invalid command, enter 'y' to confirm your order or 'n' to modify it.\n";
			}
		}
		return 0;

	}
}
//This function creates a receipt file for the user to view once they have confirmed their order.
void Order::printReceipt(string receipt) 
{
	//File called receipt.txt is created.
	ofstream myFile("receipt.txt");
	//The receipt string created within the checkout function, is passed into this function and added to receipt.txt
	myFile << receipt;
	myFile.close();
}

//This is a helper function for the calculateTotal() function. It calculates the 2-4-1 discount that the order is entitled to.
double Order::calculateDiscount() 
{
	//The below algorithm calculates the discount.
	//twoForOneCount will increase by 1, every time an item eligable for the 2-4-1 discount is found in the order.
	int twoForOneCount{ 0 };
	double discount{ 0 };
	
	//For every item in the order.
	for (auto i : items)
	{
		//If the items price is £3.99, then it will be eligable for a 2-4-1 discount.
		if (i->getPrice() == 3.99)
		{
			if (twoForOneCount != 2)
			{
				//The twoForOneCOunt is increased by 1.
				twoForOneCount = twoForOneCount + 1;

				//If two 2-4-1 items have been found in the order, then the twoForOne count will equal 2, meaning a discount can be applied to the order.
				if (twoForOneCount == 2)
				{
					//The price of one of the 2 items is then added to the discount.
					discount = discount + i->getPrice();
					//The counter is set back to 0, and can be incremented again once more 2-4-1 items are found.
					twoForOneCount = 0;
				}

			}

		}
	}
	//The calculated discount is then returned.
	return discount;
}

//Checks to see if the item the user wants to remove is valid.
bool Order::isChoiceOkay(int index) 
{
	//If the user tries to remove an item using an index number that is bigger or smaller than the sixe of the items vector, then it is invalid.
	if (index > items.size() || index <= 0) 
	{
		return false;
	}
	//Else, its valid.
	else 
	{
		return true;
	}
}


