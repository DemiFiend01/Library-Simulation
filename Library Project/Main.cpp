/** @file */

///
/// Library.cpp
///  Library project
///
/// Created by Magdalena Rapala
///
#include <iostream>
#include <vector> //for adding more books to user's collection
#include <fstream> //for files
#include <string>
#include <windows.h>//for colours
#include <chrono> //for sleep
#include <conio.h> //_kbhit()
#include "Classes.h"
#include "Library_Class.h"
using namespace std;

/** Library project

@return if the program executed successfully, 0 is returned
@return	if there are problems of some sort with the I/O files, 1 is returned

*/

void WaitForInput() ///a function WaitForInput that takes nothing; returns nothing; it clears the cin and sleeps for a bit *snore*
{
	cin.clear();
	while (!_kbhit())
	{
		Sleep(100);
	}
	cin.clear();
}
inline void UserOptions(Admin& _admin, User& _user, Library& lib, string& userfile, string& bookfile); ///for the signing in from the adminoptions menu

void AdminOptions(Admin &_admin, User &_user, Library &lib, string& userfile, string& bookfile) ///a function AdminOptions that takes an Admin _admin, User _user, Library lib, strings userfile and bookfile all by a reference; returns nothing; its a menu for an admin
{
	bool correctdata = false; int choice; ///an int choice is for the options
	system("cls"); colour(10);
	cout << "Admin MENU"; colour(7); 
	cout << " - admin: " << _admin.username << endl << "Options : " << endl << "1. Add User" << endl << "2. Add a Book" << endl;
	cout<< "3. List all Books" << endl << "4. Log out" << endl << "5. End the program" << endl << "Type in (1 - 5) your choice : ";
	cin.clear();
	do{
		cin >> choice;
		if (choice > 0 && choice < 6)
			correctdata = true;
		else
			cout << "Incorrect data. Try again: "; cin.clear(); cin.ignore(100, '\n'); //so that it repeats only once
	} while (correctdata == false);
	switch (choice)
	{
		case 1:
		{
			cin.clear();
			lib.AddUser();
			Sleep(300);
			cout << "Press anything to come back";
			WaitForInput();
			Sleep(100);
			AdminOptions(_admin, _user, lib, userfile, bookfile);
			break;
		}
		case 2:
		{
			cin.clear();
			lib.AddBook();
			Sleep(300);
			cout << "Press anything to come back";
			WaitForInput();
			Sleep(100);
			AdminOptions(_admin, _user, lib, userfile, bookfile);
			break;
		}
		case 3:
		{
			cin.clear();
			lib.ListAllBooks();
			Sleep(300);
			cout << "Press anything to come back";
			WaitForInput();
			Sleep(100);
			AdminOptions(_admin, _user, lib, userfile, bookfile);
			break;

		}
		case 4:
		{
			User _user; bool choice;
			system("cls");
			cin.clear();
			lib.LoggingIn(_user, _admin, choice);
			if (choice == 1) //signed in as an admin
			{
				system("cls");
				AdminOptions(_admin, _user,lib, userfile, bookfile);
			}
			else //signed in as a user
			{
				system("cls");
				UserOptions(_admin, _user, lib, userfile, bookfile);
			}
			break;
		}
		case 5:
			break;
	}
}

void UserOptions(Admin &_admin,User &_user,Library& lib, string& userfile, string& bookfile) ///a function UserOptions that takes an Admin _admin, User _user, Library lib, strings userfile and bookfile all by a reference; returns nothing; its a menu for a user
{
	bool correctdata = false; int choice;
	cin.clear();
	system("cls"); colour(10);
	cout << "User MENU";; colour(7); cout << " - user: " << _user.username << endl << "Books borrowed: "; colour(7); 
	cout << _user.HowManyBorrowed()<< endl << "Options : " << endl << "1. Borrow a book" << endl << "2. Return a book" << endl;
	cout<< "3. View your borrowed books" << endl << "4. Log out" << endl << "5. End the program" << endl << "Type in (1-5) your choice: ";

	do {
		cin >> choice;// cin.ignore(1000, '\n');
		if (choice > 0 && choice < 6)
			correctdata = true;
		else
			cout << "Incorrect data. Try again: "; cin.clear(); cin.ignore(100,'\n'); //so that it repeats only once
	} while (correctdata == false);
	switch (choice)
		{
			case 1: //borrow a book
				{
					lib.BookBorrow(_user,userfile);
					Sleep(300);
					cout << "Press anything to come back";
					WaitForInput();
					Sleep(100);
					UserOptions(_admin, _user, lib, userfile, bookfile);
					break;
				}
			case 2: //return a book
				{
					lib.BookReturn(_user);
					Sleep(300);
					cout << "Press anything to come back";
					WaitForInput();
					Sleep(100);
					UserOptions(_admin, _user, lib, userfile, bookfile);
					break;
				}
			case 3: //view your books
				{
					system("cls");
					cin.clear();
					_user.PrintBorrowed();
					Sleep(300);
					cout << "Press anything to come back";
					WaitForInput();
					Sleep(100);
					UserOptions(_admin, _user, lib, userfile, bookfile);
					break;
				}
			case 4: //log out
				{
					bool _choice;
					system("cls");
					cin.clear();
					lib.LoggingIn(_user, _admin, _choice);
					if (_choice == 1) //signed in as an admin
					{
						system("cls");
						_admin.PrintUser();
						AdminOptions(_admin,_user, lib, userfile, bookfile);
					}
					else //signed in as a user
					{
						system("cls");
						_user.PrintUser();
						UserOptions(_admin, _user, lib, userfile, bookfile);
					}
					break;
				}
			case 5: //end the program
				{
					return;
				}
		}
	Sleep(100);
}

void Program(Library &lib, string &adminfile, string&userfile, string&bookfile) ///a function Program that takes a Library lib, three strings: adminfile, userfile and bookfile all by a refenrence; returns nothing; manages the files and starts the library project
{
	lib.ReadAdminsFromFile(adminfile);
	lib.ReadBooksFromFile(bookfile);
	lib.ReadUsersFromFile(userfile);

	bool choice; //1-admin 0-user
	User _user; Admin _admin;
	lib.LoggingIn(_user, _admin, choice);
	if (choice == 1) //signed in as an admin
	{
		AdminOptions(_admin,_user,lib,userfile,bookfile);
	}
	else //signed in as a user
	{
		UserOptions(_admin,_user,lib, userfile, bookfile);
	}
	lib.SaveAdmins(adminfile);
	lib.SaveBooks(bookfile);
	lib.SaveUsers(userfile);
}

int main()
{
	string admin{ "admins.txt" }, users{ "users.txt" }, books{ "books.txt" }; //the file names
	Library Lib;
	Program(Lib,admin,users,books);
	return 0;
}