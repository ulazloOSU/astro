/**************************************************************************
*                                menu.hpp
* The menu header file declares the Menu class and the mainMenu function
* and its options. It also contains a vector with all of the menu options.
*
**************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>
#include "game.hpp"

using std::vector; 
using std::string;

class Menu {
	private:
		Game game;
		vector<string> mainMenuOpts;
		vector<string> endMenuOpts;

	protected:

	public:
		Menu(Game game);
		int mainMenu();
		int endMenu();
		int userSelect(int numOpts);
		int printMenuOpts(vector<string> &vect);
		void genMainMenuOpts(); //Needed to refresh values displayed
};

#endif
