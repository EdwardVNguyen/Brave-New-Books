#ifndef SALEREP_HEADER
#define SALEREP_HEADER

#include "General.h"

#include <iostream>
#include <vector>

class SaleRep
{
	public:
		// accessor functions
		std::string getName() { return name; }
		std::string getAddress() { return address; }
		int getSaleToDate() { return saleToDate; }
		int getMonthlySales() { return monthlySales; }
		double getSalesBonus() { return salesBonus;  }
		
		// mutator functions
		void setName(std::string name);
		void setAddress(std::string address);
		void setSaleToDate(int saleToDate);
		void setMonthlySales(int monthlySales);
		void setSalesBonus(int salesToDate);

		// general purpose functions
		void saleRepInfo(); 

	private:
		std::string name;
		std::string address;
		int saleToDate;
		int monthlySales;
		double salesBonus;
};

void setCurrSaleRep(SaleRep& currSaleRep, std::string name_txt, std::string address_txt, int saleToDate_txt, int monthlySale_txt);

bool saleRepMenu(int option);

void saleRepList();

void specificSaleRepInfo();

void addSaleRep();

void updateSaleRep();

// functions used in updateSaleRep();
void changeSaleRepVariables(std::vector<SaleRep>& saleRepVctr, std::string name);
void changeSaleRepName(std::vector<SaleRep>& saleRepVctr, int index);
void changeSaleRepAddress(std::vector<SaleRep>& saleRepVctr, int index);
void changeSaleRepSaleToDate(std::vector<SaleRep>& saleRepVctr, int index);
void changeSaleRepMontlySales(std::vector<SaleRep>& saleRepVctr, int index);

#endif
