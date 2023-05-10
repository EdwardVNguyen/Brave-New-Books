#include "SaleRep.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// SaleRep Class functions
void SaleRep::setName(std::string name)
{
	this->name = name;
}

void SaleRep::setAddress(std::string address)
{
	this->address = address;
}

void SaleRep::setSaleToDate(int saleToDate)
{
	this->saleToDate = saleToDate;
}

void SaleRep::setMonthlySales(int monthlySales)
{
	this->monthlySales = monthlySales;
}

void SaleRep::setSalesBonus(int salesToDate)
{
	if (getSaleToDate() <= 0)
	{
		this->salesBonus = 0;
	}
	if (getSaleToDate() <= 100)
	{
		this->salesBonus = getSaleToDate() * 0.5;
	}
	if (getSaleToDate() <= 500)
	{
		this->salesBonus = getSaleToDate() * 0.4;
	}
	if (getSaleToDate() <= 1000)
	{
		this->salesBonus = getSaleToDate() * 0.3;
	}
	if (getSaleToDate() <= 10000)
	{
		this->salesBonus = getSaleToDate() * 0.2;
	}
	else
	{
		this->salesBonus = getSaleToDate() * 0.1;
	}
}

void SaleRep::saleRepInfo()
{
	std::cout << getName() << "'s Info\n"
		<< "--------------------\n"
		<< "Sale representative's name: " << getName() << "\n"
		<< "Sale representative's address: " << getAddress() << "\n"
		<< "Sale representative's total sales: ";

	if (getSaleToDate() <= 0)
	{
		std::cout << "No sales\n";
	}
	else
	{
		std::cout << "$" << getSaleToDate() << "\n";
	}

	std::cout << "Sale representative's monthly sales: ";

	if (getMonthlySales() <= 0)
	{
		std::cout << "No sales\n";
	}
	else
	{
		std::cout << "$" << getMonthlySales() << "\n";
	}

	std::cout << "Sale representative's sales bonus: ";

	if (getSalesBonus() <= 0)
	{
		std::cout << "No sales bonus\n";
	}
	else
	{
		std::cout << "$" << getSalesBonus() << "\n";
	}
	
	std::cout << "--------------------\n\n";
}

// SaleRep Menu functions
void setCurrSaleRep(SaleRep& currSaleRep, std::string name_txt, std::string address_txt, int saleToDate_txt, int monthlySale_txt)
{
	currSaleRep.setName(name_txt);
	currSaleRep.setAddress(address_txt);
	currSaleRep.setSaleToDate(saleToDate_txt);
	currSaleRep.setMonthlySales(monthlySale_txt);
	currSaleRep.setSalesBonus(saleToDate_txt);
}

bool saleRepMenu(int option)
{
	while (option != 5)
	{
		std::cout << "Sale Representative Menu\n"
			<< "--------------------\n"
			<< "1. List of sale representatives\n"
			<< "2. Sale representative info\n"
			<< "3. Add sale representative\n"
			<< "4. Update sale representative\n"
			<< "5. Return to main menu\n"
			<< "--------------------\n"
			<< "Choose option: ";

		std::cin >> option;
		std::cout << "\n\n";

		switch (option)
		{
		case 1: // List of sale representatives
			saleRepList();
			break;
		case 2: // Information about a specific sale representative
			specificSaleRepInfo();
			break;
		case 3: // Adds a new sale representative
			addSaleRep();
			break;
		case 4: // Update specific sale representative's information
			updateSaleRep();
			break;
		case 5:
			return false;
		}
	}
	return true;
}

void saleRepList()
{
	std::ifstream saleRepFile;
	saleRepFile.open("saleRepList.txt");

	if (saleRepFile.is_open())
	{
		// reads each client in saleRepList.txt and prints each sale representative's into in terminal
		std::string name_txt, address_txt;
		int saleToDate_txt, monthlySale_txt;

		while (saleRepFile >> name_txt >> address_txt >> saleToDate_txt >> monthlySale_txt)
		{
			SaleRep currSaleRep;
			setCurrSaleRep(currSaleRep, name_txt, address_txt, saleToDate_txt, monthlySale_txt);

			currSaleRep.saleRepInfo();
		}
	}
	else
	{
		std::cout << "saleRepList file could not be found\n\n";
	}
}

void specificSaleRepInfo()
{
	std::string userInput;
	std::cin.ignore();

	// Ask user for sale representative's name
	std::cout << "Sale representative's name: ";
	std::cin >> userInput;
	std::cout << "\n";

	std::ifstream saleRepFile;
	saleRepFile.open("saleRepList.txt");

	if (saleRepFile.is_open())
	{
		std::string name_txt, address_txt;
		int saleToDate_txt, monthlySale_txt;

		// Loops through all sale representatives until matching names are found
		while (saleRepFile >> name_txt >> address_txt >> saleToDate_txt >> monthlySale_txt)
		{
			if (userInput == name_txt)
			{
				SaleRep currSaleRep;
				setCurrSaleRep(currSaleRep, name_txt, address_txt, saleToDate_txt, monthlySale_txt);

				currSaleRep.saleRepInfo();

				return;
			}
		}
		std::cout << "Sale representative could not be found!\n\n";
	}
	else
	{
		std::cout << "saleRepList file could not be found\n\n";
	}
}

void addSaleRep()
{
	std::string userName_txt, userAddress_txt;
	int userSaleToDate_txt, userMonthlySales_txt;

	std::cin.ignore();

	// ask user for sale rep's name
	std::cout << "Sale representative's name: ";
	std::getline(std::cin, userName_txt);
	spaceToUnderscore(userName_txt);
	std::cout << "\n";

	// ask user for sale rep's address
	std::cout << "Sale representative's address: ";
	std::getline(std::cin, userAddress_txt);
	spaceToUnderscore(userAddress_txt);
	std::cout << "\n";

	// ask user for sale rep's sales
	std::cout << "Sale representative's sales: ";
	std::cin >> userSaleToDate_txt;
	std::cout << "\n";

	// ask user for sale rep's monthly sales
	std::cout << "Sale representative's last month sales: ";
	std::cin >> userMonthlySales_txt;
	std::cout << "\n";

	std::ofstream saleRepFile;
	saleRepFile.open("saleRepList.txt", std::ios_base::app);

	if (saleRepFile.is_open())
	{
		saleRepFile << "\n" << userName_txt << "\n" << userAddress_txt << "\n" << userSaleToDate_txt << "\n" << userMonthlySales_txt;

		std::cout << "Sale representative added successfully!\n\n";
	}
	else
	{
		std::cout << "saleRep file could not be found\n\n";
	}
}

void updateSaleRep()
{
	std::string name_txt, address_txt;
	int saleToDate_txt, monthlySales_txt;
	std::vector<SaleRep> saleReps;

	std::ifstream readSaleRepFile;
	readSaleRepFile.open("saleRepList.txt");

	if (readSaleRepFile.is_open())
	{
		while (readSaleRepFile >> name_txt >> address_txt >> saleToDate_txt >> monthlySales_txt)
		{
			SaleRep currSaleRep;
			setCurrSaleRep(currSaleRep, name_txt, address_txt, saleToDate_txt, monthlySales_txt);
			saleReps.push_back(currSaleRep);
		}
	}
	else
	{
		std::cout << "saleRepList file could not be found\n\n";
	}

	// ask user for sale representative's name, then ask what they want to change
	std::cout << "Sale representative's name: ";
	std::cin >> name_txt;
	std::cout << "\n";

	// goes through vector to find sale representative, then ask user what they want to change
	changeSaleRepVariables(saleReps, name_txt);

	// recreates saleRepList.txt with new information
	std::ofstream writeSaleRepFile;
	writeSaleRepFile.open("saleRepList.txt");

	if (writeSaleRepFile.is_open())
	{
		for (int i = 0; i < saleReps.size(); ++i)
		{
			writeSaleRepFile << saleReps.at(i).getName() << "\n";
			writeSaleRepFile << saleReps.at(i).getAddress() << "\n";
			writeSaleRepFile << saleReps.at(i).getSaleToDate() << "\n";
			writeSaleRepFile << saleReps.at(i).getMonthlySales() << "\n";
		}
	}
	else
	{
		std::cout << "saleRepList file could not be found\n\n";
	}
}

// functions used in updateSaleRep()
void changeSaleRepVariables(std::vector<SaleRep>& saleRepVctr, std::string name)
{
	for (int i = 0; i < saleRepVctr.size(); ++i)
	{
		if (saleRepVctr.at(i).getName() == name)
		{
			// change sale representative's name option
			changeSaleRepName(saleRepVctr, i);

			// change sale representative's address option
			changeSaleRepAddress(saleRepVctr, i);

			// change sale representative's total sales option
			changeSaleRepSaleToDate(saleRepVctr, i);

			// change sale representative's monthly sales option
			changeSaleRepMontlySales(saleRepVctr, i);

			std::cout << "Sale representative's information updated!\n\n";

			return;
		}
	}
	std::cout << "Sale representative  could not be found!\n\n";
}

void changeSaleRepName(std::vector<SaleRep>& saleRepVctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change sale representative's name?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		std::string userName_txt;

		std::cin.ignore();

		std::cout << "Sale Representative's new name: ";
		std::getline(std::cin, userName_txt);
		spaceToUnderscore(userName_txt);
		std::cout << "\n";

		saleRepVctr.at(index).setName(userName_txt);
	}
	else
	{
		return;
	}

}

void changeSaleRepAddress(std::vector<SaleRep>& saleRepVctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change sale representative's address?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		std::string userAddress_txt;

		std::cin.ignore();

		std::cout << "Sale representatives's new address: ";
		std::getline(std::cin, userAddress_txt);
		spaceToUnderscore(userAddress_txt);
		std::cout << "\n\n";

		saleRepVctr.at(index).setAddress(userAddress_txt);
	}
	else
	{
		return;
	}
}

void changeSaleRepSaleToDate(std::vector<SaleRep>& saleRepVctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change sale representatives's sales?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		std::string userSalesToDate_txt;

		std::cout << "Sale representative's new sale: ";
		std::cin >> userSalesToDate_txt;
		std::cout << "\n\n";

		saleRepVctr.at(index).setSaleToDate(std::stoi(userSalesToDate_txt)); // stoi converts string to int
	}
	else
	{
		return;
	}
}

void changeSaleRepMontlySales(std::vector<SaleRep>& saleRepVctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change sale representative's monthly sales?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		std::string userMonthlySales_txt;

		std::cout << "Sale representative's new monthly sales: ";
		std::cin >> userMonthlySales_txt;
		std::cout << "\n\n";

		saleRepVctr.at(index).setMonthlySales(std::stoi(userMonthlySales_txt)); // stoi converts string to int
	}
	else
	{
		return;
	}
}