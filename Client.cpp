#include "Client.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// mutator functions
void Client::setName(std::string name)
{
	this->name = name;
}

void Client::setAddress(std::string address)
{
	this->address = address;
}

void Client::setSaleToDate(int saleToDate)
{
	this->saleToDate = saleToDate;
}

// Client class functions
void Client::clientInfo()
{
	std::cout << getName() << "'s Info\n"
		<< "--------------------\n"
		<< "Client's name: " << getName() << "\n"
		<< "Client's address: " << getAddress() << "\n"
		<< "Client's total sales: ";

	if (getSaleToDate() <= 0)
	{
		std::cout << "No sales\n";
	}
	else
	{
		std::cout << "$" << getSaleToDate() << "\n";
	}

	std::cout << "--------------------\n\n";
}

// Client menu functions
void setCurrClient(Client& currClient, std::string name_txt, std::string address_txt, int saleToDate_txt)
{
	currClient.setName(name_txt);
	currClient.setAddress(address_txt);
	currClient.setSaleToDate(saleToDate_txt);
}

bool clientMenu(int option)
{
	while (option != 5)
	{
		std::cout << "Client Menu\n"
			<< "--------------------\n"
			<< "1. List of clients\n"
			<< "2. Client info\n"
			<< "3. Add client\n"
			<< "4. Update client\n"
			<< "5. Return to main menu\n"
			<< "--------------------\n"
			<< "Choose option: ";

		std::cin >> option;
		std::cout << "\n\n";

		switch (option)
		{
		case 1: // List of clients
			clientList();
			break;
		case 2: // Information about a specific client
			specificClientInfo();
			break;
		case 3: // Adds new client
			addClient();
			break;
		case 4: // Update specific client's information
			updateClient();
			break;
		case 5:
			return false;
		}
	}
	return true;
}

void clientList() 
{
	std::ifstream clientFile; // ifstream reads file
	clientFile.open("clientList.txt");

	if (clientFile.is_open())
	{
		// reads each client in clientList.txt and prints each client's info in terminal
		std::string name_txt, address_txt;
		int saleToDate_txt;

		while (clientFile >> name_txt >> address_txt >> saleToDate_txt) 
		{
			Client currClient;
			setCurrClient(currClient, name_txt, address_txt, saleToDate_txt);

			currClient.clientInfo();
		} 
	}
	else
	{
		std::cout << "clientList file could not be found\n\n";
	}
}

void specificClientInfo() 
{
	std::string userInput;
	std::cin.ignore();
	
	// Ask user for client's name 
	std::cout << "Client's name: "; 
	std::cin >> userInput; 
	std::cout << "\n"; 

	std::ifstream clientFile;
	clientFile.open("clientList.txt");

	if (clientFile.is_open())
	{
		std::string name_txt, address_txt;
		int saleToDate_txt;

		// Loops through all clients until matching names are found, else it prints client could not be found
		while (clientFile >> name_txt >> address_txt >> saleToDate_txt) 
		{
			if (userInput == name_txt)
			{
				Client currClient;
				setCurrClient(currClient, name_txt, address_txt, saleToDate_txt);

				currClient.clientInfo();
				
				return;
			}
		}
		std::cout << "Client could not be found!\n\n";
	}
	else
	{
		std::cout << "clientList file could not be found\n\n";
	}
}

void addClient()
{
	std::string userName_txt, userAddress_txt;
	int userSaleToDate_txt;

	std::cin.ignore();

	// ask user for client's name
	std::cout << "Client's name: ";
	std::getline(std::cin, userName_txt);
	spaceToUnderscore(userName_txt);
	std::cout << "\n";
	
	// ask user for client's address
	std::cout << "Client's address: ";
	std::getline(std::cin, userAddress_txt);
	spaceToUnderscore(userAddress_txt);
	std::cout << "\n";
	
	// ask user for client's sales
	std::cout << "Client's sales: "; 
	std::cin >> userSaleToDate_txt; 
	std::cout << "\n";

	std::ofstream clientFile; // ofstream writes to file
	clientFile.open("clientList.txt", std::ios_base::app); // appends instead of overwriting clientList.txt

	if (clientFile.is_open())
	{
		clientFile << "\n" << userName_txt << "\n" << userAddress_txt << "\n" << userSaleToDate_txt;

		std::cout << "Client added successfully!\n\n";
	}
	else
	{
		std::cout << "clientList file could not be found\n\n";
	}
}


void updateClient()
{
	// Stores existing information from file into vector, ask user for client's name, changes vector, then recreates the file using new information

	std::string name_txt, address_txt;
	int saleToDate_txt;
	std::vector<Client> clients;

	// read client.txt and store it into vector
	std::ifstream readClientFile;
	readClientFile.open("clientList.txt");

	if (readClientFile.is_open())
	{
		while (readClientFile >> name_txt >> address_txt >> saleToDate_txt)
		{
			Client currClient;
			setCurrClient(currClient, name_txt, address_txt, saleToDate_txt);
			clients.push_back(currClient);
		}
	}
	else
	{
		std::cout << "clientList file could not be found\n\n";
	}

	// ask user for client's name, then ask what they want to change
	std::cout << "Client's name: ";
	std::cin >> name_txt;
	std::cout << "\n";

	// goes through vector to find client, then ask user what they want to change
	changeClientVariables(clients, name_txt);

	// recreates clientList.txt with new information
	std::ofstream writeClientFile;
	writeClientFile.open("clientList.txt");

	if (writeClientFile.is_open())
	{
		for (int i = 0; i < clients.size(); ++i)
		{
			writeClientFile << clients.at(i).getName() << "\n";
			writeClientFile << clients.at(i).getAddress() << "\n";
			writeClientFile << clients.at(i).getSaleToDate() << "\n";
		}
	}
	else
	{
		std::cout << "clientList file could not be found\n\n";
	}
}

// functions used in updateClient()
void changeClientVariables(std::vector<Client>& clientvctr, std::string name)
{

	for (int i = 0; i < clientvctr.size(); ++i)
	{
		if (clientvctr.at(i).getName() == name)
		{
			// change client's name option
			changeClientName(clientvctr, i);

			// change client's address option
			changeClientAddress(clientvctr, i);

			// change client's sales option
			changeClientSaleToDate(clientvctr, i);

			std::cout << "Client's information updated!\n\n";

			return;
		}
	}
	std::cout << "Client could not be found!\n\n";
}

void changeClientName(std::vector<Client>& clientvctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change client's name?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		std::string userName_txt;

		std::cin.ignore();

		std::cout << "Client's new name: ";
		std::getline(std::cin, userName_txt);
		spaceToUnderscore(userName_txt);
		std::cout << "\n";

		clientvctr.at(index).setName(userName_txt);
	}
	else
	{
		return;
	}
}

void changeClientAddress(std::vector<Client>& clientvctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change client's address?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		std::string userAddress_txt;

		std::cin.ignore();

		std::cout << "Client's new address: ";
		std::getline(std::cin, userAddress_txt);
		spaceToUnderscore(userAddress_txt);
		std::cout << "\n\n";

		clientvctr.at(index).setAddress(userAddress_txt);
	}
	else
	{
		return;
	}
}

void changeClientSaleToDate(std::vector<Client>& clientvctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change client's sales?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		std::string userSalesToDate_txt;

		std::cout << "Client's new sale: ";
		std::cin >> userSalesToDate_txt;
		std::cout << "\n\n";

		clientvctr.at(index).setSaleToDate(std::stoi(userSalesToDate_txt)); // stoi converts string to int
	}
	else
	{
		return;
	}
}
