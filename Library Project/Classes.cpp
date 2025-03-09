/** @file */

///
///  Classes.cpp
///  Library project
///
/// Created by Magdalena Rapala
///
#include <iostream>
#include <Windows.h>
using namespace std;

void colour(int index) ///a function that takes an int index, returns nothing, changes colour of the output based on the index
{
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, index);
}