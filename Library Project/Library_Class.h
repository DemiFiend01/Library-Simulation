/** @file */

///
///  Library_Class.h
///  Library project
///
///  Created by Magdalena Rapala
///
#ifndef LIBRARY_CLASS_H
#define LIBRARY_CLASS_H
#include <vector> //for adding more books to user's collection
#include <fstream> //for files
#include <iostream>
#include <chrono> //for sleep
#include "Classes.h"
using namespace std;

class Library ///a class Library that manages the entire library
{
private:
	vector<Admin> admins_all; ///a vector of Admin called admins_all; it contains all the admins, duh
	const int lending_limit = 4; ///a const int lending_limit is the limit to borrowed books per user
public:
	vector<Book> books_all; ///a vector of Book called books_all; it contains all the books in the library 
	vector<User> users_all; ///a vector of User called users_all; it contains all the users aka readers that are registered in the library

	void BookBorrow(User& u, string& userfile) ///a function of class Library called BookBorrow that takes a User u by a reference and a string userfile by a reference; returns nothing; it borrows a specific book from the library and adds it to the user's collection
	{
		if (u.HowManyBorrowed() == lending_limit)
		{
			system("cls");
			colour(12); cout << "You cannot borrow any more books, your lending limit has been reached." << endl; colour(7);
			return;
		}
		string title; bool was_borrowed = false;
		ListAllBooks();
		cout << "Type in title of the book you want to borrow: ";
		cin.clear();
		Sleep(200);
		getline(cin, title);
		for (auto& i : this->books_all)
		{
			if (title == i.title)
			{

				if (i.quantity > 0)
				{
					cout << "Borrowing this book for you" << endl;
					for (auto& j : u.b_borrowed)
					{
						if (j.title == i.title)
						{
							j.quantity++;
							was_borrowed = true;
							break;
						}
					}
					if (!was_borrowed)
					{
						i.quantity--;
						Book bufor = i;
						bufor.quantity = 1;
						u.b_borrowed.push_back(bufor);
					}
				}
				else
				{
					cout << "Book unavailable." << endl;
					return;
				}
			}
		}
		for (auto& i : users_all)
		{
			if (i.username == u.username)
			{
				i.b_borrowed = u.b_borrowed;
				break;
			}
		}
	}
	void BookReturn(User& u) ///a function of class Library called BookReturn that takes a User u by a reference; returns nothing, but a book specified by the user from their collection to the library's collection
	{
		system("cls");
		if (u.b_borrowed.size() == 0)
		{
			cout << "You do not have any books to return." << endl;
			return;
		}
		u.PrintBorrowed(); string title; bool returned = false;
		cout << "Type in title of the book you want to return: ";
		cin.clear();
		Sleep(200);
		getline(cin, title);
		auto i = u.b_borrowed.begin(); bool exists = false;
		while (i != u.b_borrowed.end())
		{
			if (title == i->title)
			{
				returned = true;
				cout << "Returning this book for you." << endl;
				for (auto& j : this->books_all)
					if (i->title == j.title)
					{
						j.quantity++;
						exists = true; //this book exists in the books_all vector
					}
				if (exists == false) //if this book hasn't been found in the books_all vector - add it to the vector
				{
					cout << "Thank you for your book donation!" << endl;
					this->books_all.push_back(*i);
				}
				if (i->quantity > 1)
					i->quantity--;
				else
				{
					i = u.b_borrowed.erase(i);
				}
				break;
			}
			else
				i++;
		}
		if (!returned)
		{
			cout << "You have not borrowed this book, cannot return it." << endl;
			return;
		}
		for (auto& i : users_all) //updating the users_all vector. 
		{
			if (i.username == u.username)
			{
				i.b_borrowed = u.b_borrowed;
				break;
			}
		}
	}
	void LoggingIn(User& u, Admin& a, bool& choice) ///a function of class Library called LoggingIn that takes a User u by a reference, Admin a by a reference and a bool choice by a reference; returns nothing, it's about logging into the library, either as a User or as an Admin
	{
		string name, pass;
		bool in = false;
		do {
			cout << "Library - Magdalena Rapala 2024" << endl;
			colour(13);
			cout << "Log in" << endl; colour(7);
			cout << "Type in your username and password." << endl << "Username: ";
			do {
				cin.clear();
				getline(cin, name); Sleep(100);
				if (name == "")
				{
					system("cls");
					cout << "Library - Magdalena Rapala 2024" << endl;
					colour(13);
					cout << "Log in" << endl; colour(7);
					cout << "Type in your username and password." << endl << "The username cannot be empty. Try again: ";
				}
				else
					in = true;
			} while (!in);
			in = false;
			cout << "Password: ";
			do {
				cin.clear();
				getline(cin, pass); Sleep(100);
				if (pass == "")
				{
					system("cls");
					cout << "Library - Magdalena Rapala 2024" << endl;
					colour(13);
					cout << "Log in" << endl; colour(7);
					cout << "Type in your username and password." << endl << "Username: " << name << endl;
					cout << "The password cannot be empty. Try again: ";
				}
				else
					in = true;
			} while (!in);
			in = false;
			cin.clear();
			for (auto& i : users_all)
			{
				if (name == i.username && pass == i.password)
				{
					in = true; choice = 0;
					u = i;
				}
			}
			for (auto& i : admins_all)
			{
				if (name == i.username && pass == i.password)
				{
					in = true; choice = 1;//is an admin
					a = i;
				}
			}
			if (in == 0)
			{
				cout << "Incorrect. Try again." << endl; cin.clear();
				Sleep(1000);
				system("cls");
			}
		} while (!in);
	}
	void AddUser() ///a function of class Library called AddUser that takes nothing, returns nothing, it allows to add a user (reader) to the library
	{
		system("cls");
		string username, password; bool data = true;
		cout << "Add User" << endl << "Type in the username: "; cin.clear();
		do {
			Sleep(100);
			getline(cin, username); cin.clear(); data = true;
			if (username.find(';') != username.npos)
			{
				cout << "The username cannot contain ';'. Choose a different username: ";
				data = false;
			}
			else if (username == "")
			{
				cout << "The username cannot be blank. Choose a different username: ";
				data = false;
			}
			for (auto& i : this->users_all)
			{
				if (username == i.username)
				{
					cout << "This user already exists. Choose a different username: ";
					data = false;
				}
			}
		} while (!data);
		cout << "Type in the password: ";
		do {
			Sleep(100);
			getline(cin, password); cin.clear(); data = true;
			if (password.find(';') != password.npos)
			{
				cout << "The passsword cannot contain ';'. Choose a different password: ";
				data = false;
			}
			else if (password == "")
			{
				cout << "The user HAS to have a password. Type it in: ";
				data = false;
			}
		} while (!data);

		User _user(username, password);
		users_all.push_back(_user);
		cout << endl << "The user " << username << " with the password - " << password << " has been created." << endl;
	}
	void AddBook() ///a function of class Library called AddBook that takes nothing, returns nothing; it allows to add a book the the library's catalogue (books_all)
	{
		system("cls");
		string title, author, _year, _quantity, _genrename; int year, quantity; bool already_exists = false, _by = false, _bq = false, _bg = false, deleted = false, HasSemicolonOrBlank = false; Book AlreadyExists;
		colour(10); cout << "Add a book"; colour(7); cout << " or change the quantity of an already existing one in the catalogue by typing in its title." << endl << "Type in the title : ";
		do
		{
			HasSemicolonOrBlank = false;
			cin.clear();
			Sleep(200);
			getline(cin, title);
			if (title.find(';') != title.npos)
			{
				cout << "The title cannot contain ';'. Please try again: ";
				HasSemicolonOrBlank = true;
			}
			else if (title == "")
			{
				cout << "The title cannot be blank. Please try again: ";
				HasSemicolonOrBlank = true;
			}
			for (auto i = 0; i < books_all.size(); i++)
			{
				if (title == books_all[i].title)
				{
					already_exists = true;
					cout << "This book is already in the catalogue. Please type in the new quantity (type in 0 to delete the book): ";
					do {
						cin >> _quantity;
						for (int i = 0; i < _quantity.length(); i++)
						{
							if (_quantity[i] > 47 && _quantity[i] < 72)
								_bq = true;
							else
							{
								_bq = false;
								break;
							}
						}
						if (_bq == false)
							cout << "Incorrect data, type it in again: " << endl;
						else if (stoi(_quantity) == 0)
						{
							_bq = true; deleted = true;
							cout << "Deleting the book from the library's catalogue." << endl;
							books_all.erase(books_all.begin() + i);
						}
						cin.clear(); cin.ignore();
						Sleep(10);
					} while (!_bq);
					if (!deleted)
					{
						quantity = stoi(_quantity);
						books_all[i].quantity = quantity;
					}
					break;
				}
			}

		} while (HasSemicolonOrBlank);
		if (!already_exists)
		{
			cout << "Type in the author: ";
			do
			{
				Sleep(100); cin.clear(); HasSemicolonOrBlank = false;
				getline(cin, author);
				if (author.find(';') != author.npos)
				{
					cout << "The author cannot contain ';'. Please try again: ";
					HasSemicolonOrBlank = true;
				}
				else if (author == "")
				{
					cout << "The author cannot be blank. If they are unknown, type that in instead. Please try again: ";
					HasSemicolonOrBlank = true;
				}
			} while (HasSemicolonOrBlank);
			cout << "Type in the year the book was published: ";
			do {
				cin >> _year;
				for (int i = 0; i < _year.length(); i++)
				{
					if (isdigit(_year[i]))
						_by = true;
					else
					{
						_by = false;
						break;
					}
				}
				if (_by == false)
					cout << "Incorrect year, type it in again: ";
				cin.ignore();
				Sleep(100); cin.clear();
			} while (!_by);
			year = stoi(_year);
			cout << "List of genres:" << endl;
			Genre bufor;
			bufor.ListGenres();
			cout << endl << "Type in the genre : ";
			do {
				cin >> _genrename;
				for (auto i : bufor.genres_all)
				{
					if (_genrename == i)
						_bg = true;
				}
				if (_genrename == "")
					cout << "The genre cannot be blank, type it in again: ";
				else if (_bg == false)
					cout << "Incorrect data, type it in again: ";
				cin.clear(); cin.ignore(); Sleep(100);
			} while (_bg == false);

			cout << "Type in the quantity: ";
			do {
				cin >> _quantity;
				for (int i = 0; i < _quantity.length(); i++)
				{
					if (isdigit(_quantity[i]))
						_bq = true;
					else
					{
						_by = false;
						break;
					}
				}
				if (_bq == false)
					cout << "Incorrect data, type it in again: " << endl;
				cin.clear(); cin.ignore();
				Sleep(10);
			} while (!_bq);
			quantity = stoi(_quantity);
			Book _book(title, author, year, _genrename, quantity);
			books_all.push_back(_book);
			cout << endl << "The book \"" << title << "\" made by the author " << author << endl << "that came out in the year " << year << " has been added to the catalogue with a quantity of: " << quantity << endl;
		}

	}
	void ReadUsersFromFile(const string& ifile) ///a function of class Library called ReadUsersFromFile that takes a const string ifile by a reference; returns nothing; it reads the users into the users_all vector from a file ifile
	{
		ifstream input(ifile);
		if (!input.is_open())
		{
			cout << "The file for reading users cannot be opened." << endl;
			exit(1);
		}
		string line; //a line from the input file for reading users
		while (getline(input, line))
		{
			User reader;
			size_t i = line.find(';');//size_t is basically an unsigned int but is more appropriate here
			reader.username = line.substr(0, i); //without ";"
			for (auto& i : users_all)
			{
				if (i.username == reader.username)
				{
					cout << "There appears to be an issue with usernames of users repeating in the file." << endl; //works do the same for books and admins
					exit(1);
				}
			}
			line.erase(0, i + 1);//with ";"
			i = line.find(";");
			reader.password = line.substr(0, i);
			line.erase(0, i + 1);
			i = line.find(";"); //if theres no ';' after the password - the user doesnt have any books
			while (i != string::npos)//finding the borrowed books
			{
				Book book;
				book.title = line.substr(0, i);
				line.erase(0, i + 1);
				i = line.find(";");
				book.author = line.substr(0, i);
				line.erase(0, i + 1);
				i = line.find(";");
				book.year = stoi(line.substr(0, i));
				line.erase(0, i + 1);
				i = line.find(";");
				book.genrename = line.substr(0, i);
				line.erase(0, i + 1);
				i = line.find(";");
				book.quantity = stoi(line.substr(0, i));
				line.erase(0, i + 1);
				reader.b_borrowed.push_back(book);
				i = line.find(";");//is there a next book? aka at the end of the line dont add ";"
			}
			users_all.push_back(reader);
		}
	}
	void ReadBooksFromFile(const string& ifile)/// a function of class Library called ReadBooksFromFile that takes a const string ifile by a reference; returns nothing; it reads books from a file titled ifile into a vector books_all
	{
		ifstream input(ifile);
		if (!input.is_open())
		{
			cout << "The file for reading books cannot be opened." << endl;
			exit(1);
		}
		string line;
		while (getline(input, line))
		{
			Book book;
			size_t i = line.find(";");
			book.title = line.substr(0, i);
			for (auto& i : books_all)
			{
				if (i.title == book.title)
				{
					cout << "There appears to be an issue with book titles repeating in the file." << endl;
					exit(1);
				}
			}
			line.erase(0, i + 1);
			i = line.find(";");
			book.author = line.substr(0, i);
			line.erase(0, i + 1);
			i = line.find(";");
			book.year = stoi(line.substr(0, i));
			line.erase(0, i + 1);
			i = line.find(";");
			book.genrename = line.substr(0, i);
			line.erase(0, i + 1);
			i = line.find(";");
			book.quantity = stoi(line.substr(0, i));
			line.erase(0, i + 1);
			books_all.push_back(book);
		}
	}
	void ReadAdminsFromFile(const string& ifile) ///a function of class Library called ReadAdminsFromFile that takes a const string ifile by a reference; returns nothing; reads admins from a file titled ifile into a vector admins_all
	{
		ifstream input(ifile);
		if (!input.is_open())
		{
			cout << "The file for reading admins cannot be opened." << endl;
			exit(1);
		}
		string line;
		while (getline(input, line))
		{
			Admin ad;
			size_t i = line.find(';');//size_t is basically an unsigned int but is more appropriate here
			ad.username = line.substr(0, i); //without ";"
			for (auto& i : admins_all)
			{
				if (i.username == ad.username)
				{
					cout << "There appears to be an issue with usernames of admins repeating in the file." << endl;
					exit(1);
				}
			}
			line.erase(0, i + 1);//with ";"
			i = line.find(";");
			ad.password = line.substr(0, i);
			line.erase(0, i + 1);
			admins_all.push_back(ad);
		}
	}
	void SaveUsers(const string& ofile) ///a function of class Library called SaveUsers that takes a const string ofile by a reference; returns nothing; it saves all users from a vector users_all into a file called ofile
	{
		ofstream output(ofile);
		for (auto& i : users_all)
		{
			output << i.username << ";" << i.password;
			for (size_t j = 0; j < i.b_borrowed.size(); j++)
			{
				output << ";" << i.b_borrowed[j].title << ";" << i.b_borrowed[j].author << ";" << i.b_borrowed[j].year << ";" << i.b_borrowed[j].genrename << ";" << i.b_borrowed[j].quantity;
			}

			output << endl;
		}
		output.close();
	}
	void SaveBooks(const string& ofile)///a function of class Library called SaveBooks that takes a const string ofile by a reference; returns nothing; it saves all books from a vector books_all into a file called ofile
	{
		ofstream output(ofile);
		for (auto& i : books_all)
		{
			output << i.title << ";" << i.author << ";" << i.year << ";" << i.genrename << ";" << i.quantity << endl;
		}
	}
	void SaveAdmins(const string& ofile)///a function of class Library called SaveAdmins that takes a const string ofile by a reference; returns nothing; it saves all admins from a vector admins_all into a file called ofile
	{
		ofstream output(ofile);
		for (auto& i : admins_all)
		{
			output << i.username << ";" << i.password << endl; //no ";" at the end
		}
	}
	void ListAllBooks() ///a function of class Library that takes nothing; returns nothing; simply prints out all the available books at the library from the vector books_all
	{
		system("cls");
		cout << "List of all available books at the library:" << endl;
		int counter = 1;
		for (auto& i : this->books_all)
		{
			colour(13); cout << "Book nr"; colour(7); cout << ": " << counter << endl;
			i.Print();
			counter++;
		}
	}
	void ListAllUsers() ///a function of class Library that takes nothing; returns nothing; simply prints out all the users (readers) registered at the library from the vector users_all
	{
		system("cls");
		cout << "List of all users and their borrowed books: " << endl;
		for (auto& i : this->users_all)
		{
			i.PrintUser();
			cout << endl;
			i.PrintBorrowed();
		}
	}
};
#endif