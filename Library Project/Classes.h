/** @file */

///
///  Classes.h
///  Library project
///
///  Created by Magdalena Rapala
///
#ifndef CLASSES_H
#define CLASSES_H
#include <string>
using namespace std;

///a function colour that takes an int, returns nothing, changes colour of the output
void colour(int index); 

class Genre ///a class Genre with the names of the genres, containing a string genrename and an array of strings genres_all
{
public:
	string genrename;
	string genres_all[10]{ "Fantasy", "Non-fiction", "Romance", "For children", "Horror", "Historical","Science-fiction","Mystery","Poetry","Textbook" };
	Genre() {}
	Genre(string _genrename) : genrename(_genrename) {}
	void ListGenres();
};

inline void Genre::ListGenres()///a function of class Genre called ListGenres that takes nothing, returns nothing, prints out all the genres from the genres_all
{
	for (int i = 0; i < 10; i++)
	{
		cout << i + 1 << ". " << genres_all[i] << " ";
		if ((i + 1) % 5 == 0)
			cout << endl;
	}
}

class Book : public Genre///a class Book inheriting from class Genre; it contains variables that describe a book
{
public:
	string title, author; ///strings title and author
	int year, quantity; ///int variables holding the values for year (the book was published in) and quantity (available at the library)
	Book() : year(0), quantity(0) {};
	Book(string _title, string _author, int _year, string _genre, int _quantity) : title(_title), author(_author), year(_year), quantity(_quantity) {
		this->genrename = _genre;
	}
	void Print();
};

inline void Book::Print() ///a function of class Book called Print that takes nothing, returns nothing and prints out the information about the book
{
	colour(10); cout << "Title"; colour(7); cout << ": \"" << this->title << "\"" << endl; colour(10); cout << "Author"; colour(7); cout << ": " << this->author << endl;
	colour(10); cout << "Year"; colour(7); cout << " it was published in: " << this->year << endl; colour(10); cout << "Genre: "; 
	colour(7);  cout << this->genrename << endl; colour(10); cout << "Quantity"; colour(7); cout << " available: " << this->quantity << endl;
}

class Admin ///a class Admin; it has two string variables: username and password
{
public:
	string username, password;
	Admin() {};
	Admin(string _name, string _password) : username(_name), password(_password) {}
	void PrintUser();
};

inline void Admin::PrintUser() ///a function of class Admin called PrintUser that takes nothing, returns nothing and prints all information about the user (or an admin)
{
	colour(10); cout << "Username: "; colour(7); cout << this->username; colour(10); cout << " Password: "; colour(7); cout << this->password;
}

class User : public Admin ///a class User which inherits from Admin, it has a vector of Books called b_borrowed
{
public:
	using Admin::Admin; ///using the default constructors made for Admin
	vector <Book> b_borrowed; ///a vector of books borrowed by this user ;books_borrowed 

	int HowManyBorrowed() ///a function of class User called HowManyBorrowed that takes nothing, returns an int counter; it counts all books borrowed by the user
	{
		int counter = 0;
		for (auto& i : this->b_borrowed)
			counter += i.quantity;
		return counter;
	}
	void PrintBorrowed() ///a function of class User called PrintBorrowed() that takes nothing, returns nothing and prints out all the information about all the books the user has borrowed
	{
		int count = 1;
		if (b_borrowed.size() == 0)
		{
			cout << "You have not borrowed any books" << endl;
			return;
		}
		for (auto& i : this->b_borrowed)
		{
			colour(13); cout << "Book nr "; colour(7); cout << count << ": " << endl; colour(10); cout << "Title"; colour(7); cout << ": \"" << i.title << "\"" << endl; colour(10); cout << "Author"; colour(7); cout << ": " << i.author << endl;
			colour(10); cout << "Year"; colour(7); cout << " it was published in: " << i.year << endl; colour(10); cout << "Genre: "; colour(7); cout << i.genrename << endl; colour(10); cout << "Quantity"; colour(7); cout << " that you have: " << i.quantity << endl;
			count++;
		}
	}
};


#endif
