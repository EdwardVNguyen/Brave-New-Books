#include "Client.h"
#include "SaleRep.h"
#include "Product.h"
#include "Sales.h"

#include <iostream>
#include <fstream> // to get file input & output functions
#include <string> 

bool mainMenu(int option);

int main()
{
	int option = 0; // variable that will be used for all option inputs for all menus

	mainMenu(option);

}

// menu that provides menus for client, sale rep, services, and sales
bool mainMenu(int option) 
{
	while (option != 5)
	{
		std::cout << "BRAVE NEW BOOKS\n"
			<< "--------------------\n"
			<< "1. Clients\n"
			<< "2. Sales Representatives\n"
			<< "3. Services\n"
			<< "4. Sales\n"
			<< "5. Quit\n"
			<< "--------------------\n"
			<< "Choose option: ";

		std::cin >> option;
		std::cout << "\n\n";

		switch (option)
		{
			// client's menu
			case 1: 
				clientMenu(option);
				break;
			// sales representative's menu
			case 2:
				saleRepMenu(option);
				break;
			// product's menu
			case 3:
				productMenu(option);
				break;
			// sales' menu
			case 4:
				salesMenu(option);
				break;
			case 5:
				return false;
		}
	}
	return true;
}

