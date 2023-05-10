#include "Sales.h"
#include "Product.h"
#include "Client.h"
#include "SaleRep.h"

#include <iostream>
#include <fstream>
#include <cstdlib> // for rand() 
#include <string>

// SaleHistory class functions
void SaleHistory::setClientNameSales(std::string name)
{
	this->clientName = name;
}

void SaleHistory::setSaleRepSales(std::string name)
{
	this->saleRepName = name;
}

void SaleHistory::setBookNameSales(std::string name)
{
	this->bookName = name;
}

void SaleHistory::setBookCostSales(int cost)
{
	this->bookCost = cost;
}

void SaleHistory::salesHistory()
{
	std::cout << "--------------------\n"
		<< "Client's name: " << getClientName() << "\n"
		<< "Sale representative's name: " << getSaleRep() << "\n"
		<< "Book bought by client: " << getBookName() << "\n"
		<< "Book price: $" << getBookCost() << "\n"
		<< "--------------------\n";
}

// Sales menu functions
void setCurrSaleHistory(SaleHistory& currSaleHistory, std::string clientName, std::string saleRepName, std::string bookName, int bookCost)
{
	currSaleHistory.setClientNameSales(clientName);
	currSaleHistory.setSaleRepSales(saleRepName);
	currSaleHistory.setBookNameSales(bookName);
	currSaleHistory.setBookCostSales(bookCost);
}

bool salesMenu(int option)
{
	
	while (option != 5)
	{
		std::cout << "Sales\n"
			<< "--------------------\n"
			<< "1. Purchase a book\n"
			<< "2. List all sales\n"
			<< "3. List sales from specific client\n"
			<< "4. Update sale history\n"
			<< "5. Return to main menu\n"
			<< "--------------------\n"
			<< "Choose option: ";

		std::cin >> option;
		std::cout << "\n\n";

		switch (option)
		{
			case 1: // Client purchases a book
				purchaseBook();
				break;
			case 2: // List sale history
				listAllSales();
				break;
			case 3: // List sales from specific client
				specificClientInfoSales();
				break;
			case 4: // Update sale history
				updateSalesHistory();
				break;
			case 5:
				return false;
		}

	}
	return true;
}

void purchaseBook()
{
	std::string clientName_txt;

	std::cout << "Name of client that wishes to buy: ";
	std::cin >> clientName_txt;
	std::cout << "\n";

	// Search if client exists
	std::ifstream clientFile;
	clientFile.open("clientList.txt");

	if (clientFile.is_open())
	{
		std::string name_txt, address_txt;
		int saleToDate_txt;

		while (clientFile >> name_txt >> address_txt >> saleToDate_txt)
		{
			if (clientName_txt == name_txt)
			{
				// search if book exists
				std::string nameOfBook;

				std::cout << "Name of book client wishes to buy: ";
				std::cin >> nameOfBook;
				std::cout << "\n";

				std::ifstream productFile;
				productFile.open("productList.txt");

				if (productFile.is_open())
				{
					std::string bookName_txt, bookAuthor_txt;
					int bookCost_txt, bookMonthlySales_txt;

					while (productFile >> bookName_txt >> bookAuthor_txt >> bookCost_txt >> bookMonthlySales_txt)
					{
						if (nameOfBook == bookName_txt)
						{
							// appends client's purchase to sales history 
							std::ofstream saleHistoryFile;
							saleHistoryFile.open("salesHistory.txt", std::ios_base::app);

							if (saleHistoryFile.is_open())
							{
								saleHistoryFile << "\n" << name_txt << "\n" << bookName_txt << "\n" << bookCost_txt << "\n";
								
								std::cout << "Client's purchase added successfully!\n\n";

								// Update client sales and book monthly sales
								updateClientSales(name_txt, bookCost_txt);
								updateBookMonthlySales(bookName_txt, bookCost_txt);

								// TODO: Assigns random sale representative to client and updates their sales
								std::string saleRep = assignSaleRep();
								saleHistoryFile << saleRep;
								updateSaleRepSales(saleRep, bookCost_txt);

								return;
							}
							else
							{
								std::cout << "saleHistory file could not be found\n\n";
								return;
							}

						}
					}
					std::cout << "Book could not be found\n\n";
					return;
				}
				else
				{
					std::cout << "productList file could not be found\n\n";
				}
			}
		}
		std::cout << "Client could not be found\n\n";
		return;
	}
	else
	{
		std::cout << "clientList file could not be found\n\n";
	}
}

// functions in purchaseBook()
void updateClientSales(std::string name, int cost)
{
	// stores all client information in vector
	std::string clientName_txt, clientAddress_txt;
	int clientSaleToDate_txt;
	std::vector<Client> clients;

	std::ifstream readClientFile;
	readClientFile.open("clientList.txt");

	if (readClientFile.is_open())
	{
		while (readClientFile >> clientName_txt >> clientAddress_txt >> clientSaleToDate_txt)
		{
			Client currClient;
			setCurrClient(currClient, clientName_txt, clientAddress_txt, clientSaleToDate_txt);

			if (clientName_txt == name)
			{
				currClient.setSaleToDate(clientSaleToDate_txt + cost);
			}
			clients.push_back(currClient);
		}
	}
	else
	{
		std::cout << "clientList file could not be found\n\n";
	}

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

void updateBookMonthlySales(std::string name, int cost)
{
	// stores all book's information in vector
	std::string bookName, bookAuthor;
	int bookCost, bookMonthlySales;
	std::vector<BookProduct> books;

	std::ifstream readProductFile;
	readProductFile.open("productList.txt");

	if (readProductFile.is_open())
	{
		while (readProductFile >> bookName >> bookAuthor >> bookCost >> bookMonthlySales)
		{
			BookProduct currBook;
			setCurrBook(currBook, bookName, bookAuthor, bookCost, bookMonthlySales);

			if (bookName == name)
			{
				currBook.setBookMonthlySales(bookMonthlySales + cost);
			}
			books.push_back(currBook);
		}
	}
	else
	{
		std::cout << "productList file could not be found\n\n";
	}

	// recreates productList.txt with new information
	std::ofstream writeProductFile;
	writeProductFile.open("productList.txt");

	if (writeProductFile.is_open())
	{
		for (int i = 0; i < books.size(); ++i)
		{
			writeProductFile << books.at(i).getBookName() << "\n";
			writeProductFile << books.at(i).getBookAuthor() << "\n";
			writeProductFile << books.at(i).getBookCost() << "\n";
			writeProductFile << books.at(i).getBookMonthlySales() << "\n";
		}
	}
	else
	{
		std::cout << "productList file could not be found\n\n";
	}
}

std::string assignSaleRep()
{
	// stores sale representatives information in vector
	std::string saleRepName, saleRepAddress;
	int saleRepSaleToDate, saleRepMonthlySales;
	std::vector<SaleRep> saleReps;

	std::ifstream readSaleRepFile;
	readSaleRepFile.open("saleRepList.txt");

	if (readSaleRepFile.is_open())
	{
		while (readSaleRepFile >> saleRepName >> saleRepAddress >> saleRepSaleToDate >> saleRepMonthlySales)
		{
			SaleRep currSaleRep;
			setCurrSaleRep(currSaleRep, saleRepName, saleRepAddress, saleRepSaleToDate, saleRepMonthlySales);
			saleReps.push_back(currSaleRep);
		}
	}
	else
	{
		std::cout << "saleRepList file could not be found\n\n";
	}
	// credit to K-Ballo from stackoverflow for random number generator
	// https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
	int randomNumber = std::rand() % saleReps.size();

	return saleReps.at(randomNumber).getName();
}

void updateSaleRepSales(std::string name, int cost)
{
	// stores sale representatives information in vector
	std::string saleRepName, saleRepAddress;
	int saleRepSaleToDate, saleRepMonthlySales;
	std::vector<SaleRep> saleReps;

	std::ifstream readSaleRepFile;
	readSaleRepFile.open("saleRepList.txt");

	if (readSaleRepFile.is_open())
	{
		while (readSaleRepFile >> saleRepName >> saleRepAddress >> saleRepSaleToDate >> saleRepMonthlySales)
		{
			SaleRep currSaleRep;
			setCurrSaleRep(currSaleRep, saleRepName, saleRepAddress, saleRepSaleToDate, saleRepMonthlySales);

			if (saleRepName == name)
			{
				currSaleRep.setSaleToDate(saleRepSaleToDate + cost);
				currSaleRep.setMonthlySales(saleRepMonthlySales + cost);
			}

			saleReps.push_back(currSaleRep);
		}
	}
	else
	{
		std::cout << "saleRepList file could not be found\n\n";
	}

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
// 

void listAllSales()
{
	std::ifstream saleHistoryFile;
	saleHistoryFile.open("salesHistory.txt");

	std::cout << "Sales History\n";

	if (saleHistoryFile.is_open())
	{
		// reads sales history from saleHistory.txt
		std::string clientName_txt, saleRepName_txt, bookName_txt;
		int bookCost_txt;

		while (saleHistoryFile >> clientName_txt >> bookName_txt >> bookCost_txt >> saleRepName_txt)
		{
			SaleHistory currSaleHistory;
			setCurrSaleHistory(currSaleHistory, clientName_txt, saleRepName_txt, bookName_txt, bookCost_txt);

			currSaleHistory.salesHistory();
		}
	}
	else
	{
		std::cout << "saleHistory file could not be found\n\n";
	}

}

void specificClientInfoSales()
{
	std::string userInput;
	std::cin.ignore();

	// Ask user for client's name 
	std::cout << "Client's name: ";
	std::cin >> userInput;
	std::cout << "\n";

	std::ifstream saleHistoryFile;
	saleHistoryFile.open("salesHistory.txt");

	if (saleHistoryFile.is_open())
	{
		// reads sales history from saleHistory.txt
		std::string clientName_txt, saleRepName_txt, bookName_txt;
		int bookCost_txt;

		while (saleHistoryFile >> clientName_txt >> bookName_txt >> bookCost_txt >> saleRepName_txt)
		{
			if (clientName_txt == userInput)
			{
				SaleHistory currSaleHistory;
				setCurrSaleHistory(currSaleHistory, clientName_txt, saleRepName_txt, bookName_txt, bookCost_txt);

				currSaleHistory.salesHistory();
			}
		}
	}
}

void updateSalesHistory()
{
	std::string clientName_txt, saleRepName_txt, bookName_txt;
	int bookCost_txt;
	std::vector<SaleHistory> salesHistory;

	std::ifstream readSalesHistoryFile;
	readSalesHistoryFile.open("salesHistory.txt");

	if (readSalesHistoryFile.is_open())
	{
		while (readSalesHistoryFile >> clientName_txt >> bookName_txt >> bookCost_txt >> saleRepName_txt)
		{
			SaleHistory currSaleHistory;
			setCurrSaleHistory(currSaleHistory, clientName_txt, saleRepName_txt, bookName_txt, bookCost_txt);
			salesHistory.push_back(currSaleHistory);
		}
	}
	else
	{
		std::cout << "saleHistory file could not be found\n\n";
	}

	std::cout << "Client's name: ";
	std::cin >> clientName_txt;
	std::cout << "\n";

	changeSalesHistoryVariables(salesHistory, clientName_txt);

	std::ofstream writeSalesHistoryFile;
	writeSalesHistoryFile.open("salesHistory.txt");

	if (writeSalesHistoryFile.is_open())
	{
		for (int i = 0; i < salesHistory.size(); ++i)
		{
			writeSalesHistoryFile << salesHistory.at(i).getClientName() << "\n";
			writeSalesHistoryFile << salesHistory.at(i).getBookName() << "\n";
			writeSalesHistoryFile << salesHistory.at(i).getBookCost() << "\n";
			writeSalesHistoryFile << salesHistory.at(i).getSaleRep() << "\n";
		}
	}
	else
	{
		std::cout << "salesHistory file could not be found\n\n";
	}
}

// functions used in updateSalesHistory()
void changeSalesHistoryVariables(std::vector<SaleHistory>& salesHistoryVctr, std::string name)
{
	for (int i = 0; i < salesHistoryVctr.size(); ++i)
	{
		if (salesHistoryVctr.at(i).getClientName() == name)
		{
			changeSalesHistoryName(salesHistoryVctr, i);
			changeSalesHistoryRepName(salesHistoryVctr, i);
			changeSalesHistoryCost(salesHistoryVctr, i);

			std::cout << "Sales history has been updated!\n\n";

			return;
		}
	}
	std::cout << "Client name could not be found!\n\n";
}
void changeSalesHistoryName(std::vector<SaleHistory>& saleHistoryVctr, int index)
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
		std::string userClientName_txt;

		std::cin.ignore();

		std::cout << "client's new name: ";
		std::getline(std::cin, userClientName_txt);
		spaceToUnderscore(userClientName_txt);
		std::cout << "\n";

		saleHistoryVctr.at(index).setClientNameSales(userClientName_txt);
	}
	else
	{
		return;
	}
}
void changeSalesHistoryRepName(std::vector<SaleHistory>& saleHistoryVctr, int index)
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
		std::string userSaleRepName_txt;

		std::cin.ignore();

		std::cout << "Sale representative's new name: ";
		std::getline(std::cin, userSaleRepName_txt);
		spaceToUnderscore(userSaleRepName_txt);
		std::cout << "\n";

		saleHistoryVctr.at(index).setSaleRepSales(userSaleRepName_txt);
	}
	else
	{
		return;
	}
}
void changeSalesHistoryCost(std::vector<SaleHistory>& saleHistoryVctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change book price?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		int userSaleBookCost_txt;

		std::cout << "Book's new price: ";
		std::cin >> userSaleBookCost_txt;
		
		std::cout << "\n";

		saleHistoryVctr.at(index).setBookCostSales(userSaleBookCost_txt);
	}
	else
	{
		return;
	}
}
