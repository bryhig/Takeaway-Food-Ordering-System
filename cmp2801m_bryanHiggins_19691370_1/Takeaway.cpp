
#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
#include "Order.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

int main()
{
	//Welcomes user to the application.
	cout << "=======WELCOME TO THE TAKEAWAY ORDERING SYSTEM=======\n\n";
	cout << "Please enter 'help' if you are unsure of which commands to use.\n\n";

	string userCommand;
	vector <string> parameters;

	// Create a menu object from a CSV file
	Menu menu = Menu("menu.csv");

	// Create an order object
	Order order = Order();

	while (userCommand != "exit")
	{
		//Prompts user for command.
		cout << "Please enter a command: ";
		getline(cin, userCommand);
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		char* token;
		token = strtok(cstr, " ");

		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}

		string command = parameters[0];

		if (command.compare("menu") == 0)
		{
			//Menu toString() function called to display menu.
			cout << menu.toString();
		}
		else if (command.compare("add") == 0)
		{
			//If parameters size is greater than one, then the user has input at least a second value (index) to attempt to add something to the order.
			if (parameters.size() > 1) 
			{
				    //Erases the "add" 
					parameters.erase(parameters.begin());

					//Iterates through the parameters vector, meaning users can add multiple items to their order at the same time.
					for (auto i = parameters.begin(); i != parameters.end(); ++i)
					{
						//An error could be cause if the user enters a non-integer input to add to the order, this is stopped by the catch staement below.
						try 
						{
							string token = *i;
							
							//Where the error could occur if user input is not an int.
							int itemNumber = stoi(token);

							//isChoiceOkay() function called, checks to see if choice the user has made is okay and is on the menu.
							if (menu.isChoiceOkay(itemNumber) == true)
							{
								//If choice is okay, the item is added to the order by the makeChoice() function being called.
								Item* choice = menu.makeChoice(itemNumber);
								order.add(choice);
							}
							else
							{
								//If the choice was invalid the user will be informed.
								cout << "ERROR: Invalid item selected, please select a valid number from the menu to add an item to the order.\n\n";
							}
						}
						//Catches the possible exeption that could be caused by the string to int conversion.
						catch (exception e)
						{
							cout << "ERROR: Invalid command, no index number was entered to specify which item to add.AD\n\n";
						}
					}	
			}
			//If parameters.size() == 1, then the user must've forgot to type an index number in.
			else 
			{
				cout << "ERROR: Invalid command, no index number was entered to specify which item to add.\n\n";
			}

	
		}
		else if (command.compare("remove") == 0)
		{
			//Like 'add' command, checks to see if the user enetered an index number or second value.
			if (parameters.size() == 2) 
			{
				//Trys the code below, will catch an exception if the user entered a character that wasn't an integer.
				try
				{
					string token = parameters[1];
					//Exception could be thrown here.
					int itemNumber = stoi(token);
					
					//Checks to see if users choice is okay.
					if (order.isChoiceOkay(itemNumber) == true)
					{
						order.remove(itemNumber);
					}
					else
					{
						//If choice was invalid the user is informed.
						cout << "ERROR: Invalid item selected, please enter a valid item number to remove that item from the order\n\n";
					}
				}
				//Catches possible exeption from string to int conversion.
				catch (exception e)
				{
					cout << "ERROR: Invalid command, no index number was entered to specify which item to remove. You entered: 'remove " + parameters[1] + "'\n\n";
				}
			}
			//Knows the user didnt input an index number if parameters.size() != 2.
			else 
			{
				cout << "ERROR: Invalid command, no valid index number was entered to specify which item to remove.\n\n";
			}


		}
		else if (command.compare("checkout") == 0)
		{
			//Checkout function called to display checkout screen.
			int a = order.checkout();
			//If the checkout function returns 1, it means the user has confirmed there order, therefore the program can break from while loop, and terminate gracefully.
			if (a == 1) 
			{
				//User is informed a receipt has been produced.
				cout << "A receipt file called 'receipt.txt' has been produced.\n";
				//Menu destructor called to delete all pointer objects contained in its "items" vector, and to destroy the menu itself.
				menu.~Menu();
				break;
			}

		}
		else if (command.compare("help") == 0)
		{
			//Help page displayed.
			cout << "\n===============HELP PAGE===============\n";
			cout << "Please use the one of the commands shown below. \n\n";
			cout << "menu - displays the menu.\nadd[INDEX] - adds item to the order, based on its numerical position within the menu. You can add multiple items at the same time by entering multiple index numbers.\nremove[INDEX] - removes an item from the order, based on its numerical position in the order.\n";
			cout << "checkout - displays items in the order, the total price, and discount savings.\nhelp - displays the help page (CURRENT PAGE).\nexit - exits the program.\n\n";
		}
		else 
		{
			//If the user enters an invalid command they will be informed.
			if (command.compare("exit") != 0) 
			{
				cout << "ERROR: Invalid command used, please enter 'help' if you wish to see a list of useable commands.\n\n";
			}
			
		}

		parameters.clear();

	}

	cout << "Press any key to quit...";
	std::getchar();

	return 0;

}

