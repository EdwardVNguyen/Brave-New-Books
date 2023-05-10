#ifndef PRODUCT_HEADER
#define PRODUCT_HEADER

#include "General.h"

#include <iostream>
#include <vector>

class BookProduct
{
	public:
		// accessor functions
		std::string getBookName() { return bookName; }
		std::string getBookAuthor() { return bookAuthor; }
		int getBookCost() { return bookCost; }
		int getBookMonthlySales() { return bookMonthlySales; }

		// mutator functions;
		void setBookName(std::string name);
		void setBookAuthor(std::string author);
		void setBookCost(int cost);
		void setBookMonthlySales(int monthlySales);

		// general functions 
		void bookInfo();

	private:
		std::string bookName, bookAuthor;
		int bookCost, bookMonthlySales;
};

void setCurrBook(BookProduct& currBook, std::string bookName_txt, std::string bookAuthor, int bookCost_txt, int bookMonthlySales_txt);

bool productMenu(int option);

void bookList();

void specificBookInfo();

void addBook();

void updateBook();

// functions used in updateBook()
void changeBookVariables(std::vector<BookProduct>& bookvctr, std::string name);
void changeBookName(std::vector<BookProduct>& bookvctr, int index);
void changeBookAuthor(std::vector<BookProduct>& bookvctr, int index);
void changeBookCost(std::vector<BookProduct>& bookvctr, int index);
void changeBookMonthlySale(std::vector<BookProduct>& bookvctr, int index);

#endif