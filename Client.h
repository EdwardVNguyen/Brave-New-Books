#ifndef CLIENT_HEADER
#define CLIENT_HEADER

#include "General.h"

#include <iostream>
#include <vector>

class Client
{
	public:
		// accessor functions
		std::string getName() { return name; }
		std::string getAddress() { return address; }
		int getSaleToDate() { return saleToDate; }

		// mutator functions
		void setName(std::string name);
		void setAddress(std::string address);
		void setSaleToDate(int saleToDate);

		void clientInfo();  // prints out client's name, address, and sales to date.

	private:
		std::string name;
		std::string address;
		int saleToDate;


};

void setCurrClient(Client& currClient, std::string name_txt, std::string address_txt, int saleToDate_txt);

bool clientMenu(int option); // menu that provides information on clients and functionality to change client info

void clientList();

void specificClientInfo();

void addClient();

void updateClient();

// functions used in updateClient()
void changeClientVariables(std::vector<Client>& clientvctr, std::string name);
void changeClientName(std::vector<Client>& clientvctr, int index);
void changeClientAddress(std::vector<Client>& clientvctr, int index);
void changeClientSaleToDate(std::vector<Client>& clientvctr, int index);

#endif
