#ifndef SALES_H
#define SALES_H

#include <iostream>
#include <vector>

class SaleHistory
{
	public:
		// accessor functions
		std::string getClientName() { return clientName; }
		std::string getSaleRep() { return saleRepName; }
		std::string getBookName() { return bookName; }
		int getBookCost() { return bookCost; }

		// mutator functions
		void setClientNameSales(std::string name);
		void setSaleRepSales(std::string name);
		void setBookNameSales(std::string name);
		void setBookCostSales(int cost);

		void salesHistory();

	private:
		std::string clientName;
		std::string saleRepName;
		std::string bookName;
		int bookCost;
};

void setCurrSaleHistory(SaleHistory& currSaleHistory, std::string clientName, std::string saleRepName, std::string bookName, int bookCost);

bool salesMenu(int option);

void purchaseBook();

// functions in purchaseBook()
void updateClientSales(std::string name, int cost);
void updateBookMonthlySales(std::string name, int cost);
std::string assignSaleRep(); 
void updateSaleRepSales(std::string name, int cost);
//

void listAllSales();

void specificClientInfoSales();

void updateSalesHistory();

// functions used in updateSalesHistory();
void changeSalesHistoryVariables(std::vector<SaleHistory>& salesHistoryVctr, std::string name);
void changeSalesHistoryName(std::vector<SaleHistory>& saleHistoryVctr, int index);
void changeSalesHistoryRepName(std::vector<SaleHistory>& saleHistoryVctr, int index);
void changeSalesHistoryCost(std::vector<SaleHistory>& saleHistoryVctr, int index);


#endif