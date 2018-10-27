/*********************************************************************
**                          utils.cpp                               **
** These utilities are a continually growing compilation of reusable**
** pieces of code I've found useful. See the descriptions for each  **
** individual function to see what they do.                         **
*********************************************************************/

#include "utils.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <climits>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::setfill;
using std::setw;
using std::cerr;
using std::string;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::time;
using std::srand;

//Checks if the string is a float and if it's within 
//a certain value range.
bool floatCheck(string &str, float &retFloat, float MIN_NUM, float MAX_NUM, bool canEqlMin, bool canEqlMax)
{
	bool badVal = false;
	retFloat = 0.0;
	std::size_t* pos = new std::size_t;
	try	{
		retFloat = stof(str, pos);
		if (*pos != str.length()) {
			badVal = true;
			throw std::invalid_argument("parse fail");
		} if (retFloat < MIN_NUM || (retFloat == MIN_NUM && !canEqlMin)) {
			badVal = true;
			cout << "Error: Number too small." << endl;
		} else if (retFloat > MAX_NUM || (retFloat == MAX_NUM && !canEqlMax)) {
			badVal = true;
			cout << "Error: Number too large." << endl;
		}
	} catch (std::out_of_range& e) {
		badVal = true;
		cerr << "Error: Number is out of range." << endl;
	} catch (std::invalid_argument& e) {
		badVal = true;
		cerr << "Error: Not a valid number." << endl;
	} catch (...) {
		badVal = true;
		cout << "Invalid entry." << endl;
	}
	delete pos;
	if (badVal) { return false; }
	return true;
}

//Checks if the string is an integer and if it's within 
//a certain value range.
bool intCheck(string &str, int &retInt, int MIN_NUM, int MAX_NUM, bool canEqlMin, bool canEqlMax)
{
	bool badVal = false;
	retInt = 0;
	std::size_t* pos = new std::size_t;
	try	{
		retInt = stoi(str, pos);
		if (*pos != str.length()) {
			badVal = true;
			throw std::invalid_argument("parse fail");
		} else if (retInt < MIN_NUM || (retInt == MIN_NUM && !canEqlMin)) {
			badVal = true;
			cout << "Error: Number too small." << endl;
		} else if (retInt > MAX_NUM || (retInt == MAX_NUM && !canEqlMax)) {
			badVal = true;
			cout << "Error: Number too large." << endl;
		} 
	} catch (std::out_of_range& e) {
		badVal = true;
		cerr << "Error: Number is out of range." << endl;
	} catch (std::invalid_argument& e) {
		badVal = true;
		cerr << "Error: Not a valid number." << endl;
	} catch (...) {
		badVal = true;
		cout << "Invalid entry." << endl;
	}
	delete pos;
	if (badVal) { return false; }
	return true;
}

bool yesOrNo(string question) {
	string response = "";
	do {
		cout << question << " (y/n) ";
		getline(cin, response);
	} while(response != "y" && response != "n");

	if (response == "y") { return true; }
	else { return false; }
}

//Formatting and display function; prints a border
void printHorizontalBorder(int width, char spacer) {
	cout << setfill(spacer) << setw(width) << "" << endl;
	cout << setfill(' ');
	return;
}
