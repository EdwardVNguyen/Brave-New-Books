#include "Product.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// BookProduct class functions
void BookProduct::setBookName(std::string name)
{
	this->bookName = name;
}

void BookProduct::setBookAuthor(std::string author)
{
	this->bookAuthor = author;
}

void BookProduct::setBookCost(int cost)
{
	this->bookCost = cost;
}

void BookProduct::setBookMonthlySales(int monthlySales)
{
	this->bookMonthlySales = monthlySales;
}

void BookProduct::bookInfo()
{
	std::cout << "--------------------\n"
		<< "Book name: " << getBookName() << "\n"
		<< "Book's author: " << getBookAuthor() << "\n";

	if (getBookCost() <= 0)
	{
		std::cout << "Free\n";
	}
	else
	{
		std::cout << "Book cost: $" << getBookCost() << "\n";
	}

	if (getBookMonthlySales() <= 0)
	{
		std::cout << "No sales\n";
	}
	else
	{
		std::cout << "Book monthly sales: $" << getBookMonthlySales() << "\n";
	}

	std::cout << "--------------------\n\n";
}

// Product menu functions
void setCurrBook(BookProduct& currBook, std::string bookName_txt, std::string bookAuthor_txt, int bookCost_txt, int bookMonthlySales_txt)
{
	currBook.setBookName(bookName_txt);
	currBook.setBookAuthor(bookAuthor_txt);
	currBook.setBookCost(bookCost_txt);
	currBook.setBookMonthlySales(bookMonthlySales_txt);
}

bool productMenu(int option)
{
	while (option != 5)
	{
		std::cout << "Books Menu\n"
			<< "--------------------\n"
			<< "1. List of books\n"
			<< "2. Specific book info\n"
			<< "3. Add a book\n"
			<< "4. Update a book\n"
			<< "5. Return to main menu\n"
			<< "--------------------\n"
			<< "Choose option: ";

		std::cin >> option;
		std::cout << "\n\n";

		switch (option)
		{
		case 1: // List of books
			bookList();
			break;
		case 2: // Information about a specific book
			specificBookInfo();
			break;
		case 3: // Adds a new book
			addBook();
			break;
		case 4: // Update a specific book
			updateBook();
			break;
		case 5:
			return false;
		}
	}
	return true;
}

void bookList()
{
	std::ifstream productFile;
	productFile.open("productList.txt");

	std::cout << "List of Books\n";

	if (productFile.is_open())
	{
		// reads each book in productList.txt and prints out each book's information in terminal
		std::string bookName_txt, bookAuthor_txt;
		int bookCost_txt, bookMonthlySales_txt;

		while (productFile >> bookName_txt >> bookAuthor_txt >> bookCost_txt >> bookMonthlySales_txt)
		{
			BookProduct currBook;
			setCurrBook(currBook, bookName_txt, bookAuthor_txt, bookCost_txt, bookMonthlySales_txt);

			currBook.bookInfo();
		}
	}
	else
	{
		std::cout << "productList file could not be found\n\n";
	}
	
}

void specificBookInfo()
{
	std::string userInput;
	std::cin.ignore();

	// Ask user for book's name
	std::cout << "Book name: ";
	std::cin >> userInput;
	std::cout << "\n";

	std::ifstream productFile;
	productFile.open("productList.txt");

	if (productFile.is_open())
	{
		std::string bookName_txt, bookAuthor_txt;
		int bookCost_txt, bookMonthlySales_txt;

		// Loops through all books until matching names are found, else it prints book could not be found
		while (productFile >> bookName_txt >> bookAuthor_txt >> bookCost_txt >> bookMonthlySales_txt)
		{
			if (userInput == bookName_txt)
			{
				BookProduct currBook;
				setCurrBook(currBook, bookName_txt, bookAuthor_txt, bookCost_txt, bookMonthlySales_txt);

				currBook.bookInfo();

				return;
			}
			std::cout << "Book could not be found!\n\n";
		}
	}
	else
	{
		std::cout << "productList file could not be found\n\n";
	}
}

void addBook()
{
	std::string bookName_txt, bookAuthor_txt;
	int bookCost_txt, bookMonthlySales_txt;

	std::cin.ignore();

	// ask user for book's name
	std::cout << "Book name: ";
	std::getline(std::cin, bookName_txt);
	spaceToUnderscore(bookName_txt);
	std::cout << "\n";

	// ask user for book's author
	std::cout << "Book's author: ";
	std::getline(std::cin, bookAuthor_txt);
	spaceToUnderscore(bookAuthor_txt);
	std::cout << "\n";

	// ask user for book's cost
	std::cout << "Book's cost: ";
	std::cin >> bookCost_txt;
	std::cout << "\n";

	// ask user for book's monthly sales
	std::cout << "Last month book sales: ";
	std::cin >> bookMonthlySales_txt;
	std::cout << "\n";

	std::ofstream productFile;
	productFile.open("productList.txt", std::ios_base::app);

	if (productFile.is_open())
	{
		productFile << "\n" << bookName_txt << "\n" << bookAuthor_txt << "\n" << bookCost_txt << "\n" << bookMonthlySales_txt;

		std::cout << "Book added successfully!\n\n";
	}
	else
	{
		std::cout << "productList file could not be found\n\n";
	}
}

void updateBook()
{
	std::string bookName_txt, bookAuthor_txt;
	int bookCost_txt, bookMonthlySale_txt;
	std::vector<BookProduct> books;

	std::ifstream readProductFile;
	readProductFile.open("productList.txt");

	if (readProductFile.is_open())
	{
		while (readProductFile >> bookName_txt >> bookAuthor_txt >> bookCost_txt >> bookMonthlySale_txt)
		{
			BookProduct currBook;
			setCurrBook(currBook, bookName_txt, bookAuthor_txt, bookCost_txt, bookMonthlySale_txt);
			books.push_back(currBook);
		}
	}
	else
	{
		std::cout << "productList file could not be found\n\n";
	}

	std::cout << "Book's name: ";
	std::cin >> bookName_txt;
	std::cout << "\n";

	changeBookVariables(books, bookName_txt);

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

// functions used in updateBook()
void changeBookVariables(std::vector<BookProduct>& bookvctr, std::string name)
{
	for (int i = 0; i < bookvctr.size(); ++i)
	{
		if (bookvctr.at(i).getBookName() == name)
		{
			changeBookName(bookvctr, i);
			changeBookAuthor(bookvctr, i);
			changeBookCost(bookvctr, i);
			changeBookMonthlySale(bookvctr, i);
			
			std::cout << "Book has been updated!\n\n";

			return;
		}
	}
	std::cout << "Book could not be found!\n\n";
}
void changeBookName(std::vector<BookProduct>& bookvctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change book's name?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		std::string userBookName_txt;

		std::cin.ignore();

		std::cout << "Book's new name: ";
		std::getline(std::cin, userBookName_txt);
		spaceToUnderscore(userBookName_txt);
		std::cout << "\n";

		bookvctr.at(index).setBookName(userBookName_txt);
	}
	else
	{
		return;
	}
}
void changeBookAuthor(std::vector<BookProduct>& bookvctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change book's author?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		std::string userBookAuthor_txt;

		std::cin.ignore();

		std::cout << "Book's new author: ";
		std::getline(std::cin, userBookAuthor_txt);
		spaceToUnderscore(userBookAuthor_txt);
		std::cout << "\n";

		bookvctr.at(index).setBookAuthor(userBookAuthor_txt);
	}
	else
	{
		return;
	}
}
void changeBookCost(std::vector<BookProduct>& bookvctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change book's cost?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		int userBookCost_txt;

		std::cin.ignore();

		std::cout << "Book's new cost: ";
		std::cin >> userBookCost_txt;
		std::cout << "\n";

		bookvctr.at(index).setBookCost(userBookCost_txt);
	}
	else
	{
		return;
	}
}
void changeBookMonthlySale(std::vector<BookProduct>& bookvctr, int index)
{
	int option;

	std::cout << "--------------------\n"
		<< "Do you want to change book's monthly sales?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "--------------------\n";

	std::cin >> option;
	std::cout << "\n\n";

	if (option == 1)
	{
		int userBookMonthlySales_txt;

		std::cin.ignore();

		std::cout << "Book's new monthlySales: ";
		std::cin >> userBookMonthlySales_txt;
		std::cout << "\n";

		bookvctr.at(index).setBookMonthlySales(userBookMonthlySales_txt);
	}
	else
	{
		return;
	}
}