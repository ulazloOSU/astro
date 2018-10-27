/*
 * game.cpp
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include "game.hpp"
#include "critter.hpp"
#include "ant.hpp"
#include "db.hpp"
#include "utils.hpp"

using std::cout;
using std::endl;
using std::to_string;
using std::setw;
using std::left;
using std::vector;
using std::rand;

//Initial menu values
Game::Game() { 
	this->userSteps = 100;
	this->gridRows = 20;
	this->gridCols = 20;
	this->startNumAnts = 99;
	this->startNumDB = 5;
	grid = oldGrid = NULL;
}
/*
Game::~Game() {
	deleteGrid(oldGrid);
	deleteGrid(grid);
}
*/
//Allocates all of the elements for a grid and returns it
void Game::createGrid(Critter*** &newGrid) {
	newGrid = new Critter**[gridRows];
	for (int i = 0 ; i < gridRows ; ++i) {
		newGrid[i] = new Critter*[gridCols];
		for (int j = 0 ; j < gridCols ; ++j) {
			newGrid[i][j] = NULL;
		}
	}
}

//Deallocates all of the elements of a grid
void Game::deleteGrid(Critter*** &delGrid) {
	for (int i = 0 ; i < gridRows ; ++i) {
		for (int j = 0 ; j < gridCols ; ++j) {
			if (delGrid[i][j])
				delete delGrid[i][j];
		}
		delete [] delGrid[i];
	}
	delete [] delGrid;	
	delGrid = NULL;
}

//Puts the starting numbers of each of the critters on the grid
void Game::populateGrid(Critter*** &tmp) {
	int r, c; //Generic variables for coordinates
	
	//Generate the doodlebugs
	for (int i = 0 ; i < startNumDB ; ++i) {
		do { 
			r = rand() % gridRows;
			c = rand() % gridCols;
		} while (tmp[r][c]);
		tmp[r][c] = new DB(r,c);
	}	
	
	//Generate the ants
	for (int i = 0 ; i < startNumAnts ; ++i) {
		do { 
			r = rand() % gridRows;
			c = rand() % gridCols;
		} while (tmp[r][c]);
		tmp[r][c] = new Ant(r,c);
	}
}

void Game::runSim() {
	//Set up initial state of grids
	createGrid(grid);
	populateGrid(grid);
	cout << "Step 0" << endl;
	printGrid();

	for ( int i = 1 ; i < userSteps+1 ; ++i ) {
		oldGrid = grid; //Maintain grid's current state
		grid = NULL;
		createGrid(grid); //Create new grid for moves to take place on
		move();
		breed();
		starve();
		//cout << "Deleting old grid." << endl;
		deleteGrid(oldGrid); //Delete old state of grid
		cout << "Step " << i << endl;
		printGrid();
	}
	deleteGrid(grid);
	grid = NULL;
}

void Game::move() {
	Direction mvDir = Direction::NONE; //Generic variables
	Critter* tmpCrit = NULL;
	int newCol = 0, newRow = 0;

	//cout << "Doodlebugs begin to move." << endl;
	//Doodlebugs move first
	for ( int r = 0 ; r < gridRows ; ++r ) {
		for ( int c = 0 ; c < gridCols ; ++c ) {
			if (oldGrid[r][c] && oldGrid[r][c]->getState()) {
				//Acquire a move direction (including NONE)
				mvDir = dirSelect(oldGrid[r][c], false);
				//Move the DB object and get the new Critter
				tmpCrit = oldGrid[r][c]->move(mvDir);
				//Get the new, post-move row/col
				newRow = tmpCrit->getRow();
				newCol = tmpCrit->getCol();
				//Set the DB from the old grid on the new grid
				grid[newRow][newCol] = tmpCrit;
				tmpCrit = NULL;
			}
		}
	}

	//cout << "Ants begin to move." << endl;
	//Ants move second
	for ( int r = 0 ; r < gridRows ; ++r ) {
		for ( int c = 0 ; c < gridCols ; ++c ) {
			//Check if its an ant and if a DB occupies its current spot on the new grid (ie eaten)
			if (oldGrid[r][c] && !oldGrid[r][c]->getState() && !(grid[r][c] && grid[r][c]->getState())) {
				//Acquire a move direction
				mvDir = dirSelect(oldGrid[r][c], false);
				//Move the ant object and get the new critter
				tmpCrit = oldGrid[r][c]->move(mvDir);
				//Get the new post-move row/col
				newRow = tmpCrit->getRow();
				newCol = tmpCrit->getCol();
				//Set the Ant from the old grid on the new grid
				grid[newRow][newCol] = tmpCrit;
				tmpCrit = NULL;
			}
		}
	}
}

//All critters have moved, use "grid" not "oldGrid"
void Game::breed() {
	Direction breedDir = Direction::NONE;
	Critter* bredCrit = NULL;
	int breedRow, breedCol;

	//NOTE: Specs state that "The doodlebugs will move before the ants
	//each time step." I don't know if this means the DBs will breed
	//before the ants as well, however, since that's the more 
	//complicated case, I've written that below. If doodlebugs and ants
	//can breed at the same time, condense the below sections into
	//one section whereby both critters breed. 


	//NEED TO SKIP OVER THE BABIES


	//cout << "Doodlebugs begin to breed." << endl;
	//Doodlebugs breed first
	for ( int r = 0 ; r < gridRows ; ++r ) {
		for ( int c = 0 ; c < gridCols ; ++c ) {
			if (grid[r][c] && grid[r][c]->getState()) {
				//Get the direction of breeding
				breedDir = dirSelect(grid[r][c], true);
				//Attempt to breed
				bredCrit = grid[r][c]->breed(breedDir);
				//Can't breed; no open spaces
				if (!bredCrit) { }
				//Breed into adjacent grid space
				else { 
					breedRow = bredCrit->getRow();
					breedCol = bredCrit->getCol();
					grid[breedRow][breedCol] = bredCrit; 
				}
				bredCrit = NULL;
			}
		}
	}
				
	//cout << "Ants begin to breed." << endl;
	//Ants breed second
	for ( int r = 0 ; r < gridRows ; ++r ) {
		for ( int c = 0 ; c < gridCols ; ++c ) {
			if (grid[r][c] && !grid[r][c]->getState()) {
				//Get the direction of breeding
				breedDir = dirSelect(grid[r][c], true);
				//Attempt to breed
				bredCrit = grid[r][c]->breed(breedDir);
				//Can't breed; no open spaces
				if (!bredCrit) { }
				//Breed into adjacent grid space
				else { 
					breedRow = bredCrit->getRow();
					breedCol = bredCrit->getCol();
					grid[breedRow][breedCol] = bredCrit; 
				}
				bredCrit = NULL;
			}
		}
	}
}

//Starves doodlebugs that reach 3 steps
void Game::starve() {
	//cout << "Doodlebugs begin to starve." << endl;
	for ( int r = 0 ; r < gridRows ; ++r ) {
		for ( int c = 0 ; c < gridCols ; ++c ) {
			//Kill DB if 3 steps pass without eating
			if (grid[r][c] && grid[r][c]->getState() >= 4) {
				delete grid[r][c];
				grid[r][c] = NULL;
			}
		}
	}
}

//Checks directions the critter can move that arent out of bounds or already occupied
Direction Game::dirSelect(Critter* &crit, bool breedCall) {
	vector<Direction> dirVec;
	int r = crit->getRow(),
		c = crit->getCol();
	
	//Directions available during a normal move
	if (crit && !breedCall) {
		//Directions a DB can move to eat ants
		//Checks for boundaries
		//Checks if something is occupying the space (to up or left) on new grid (other DB ate it)
		//Checks if there's an ant around it; has to check oldGrid for ants (they haven't moved yet)
		if (crit->getState()) { 
			if (r > 0 && !grid[r-1][c] && oldGrid[r-1][c] && !oldGrid[r-1][c]->getState())
				dirVec.push_back(Direction::EATUP);
			if (c < gridCols-1 && !grid[r][c+1] && oldGrid[r][c+1] && !oldGrid[r][c+1]->getState())
				dirVec.push_back(Direction::EATRIGHT);
			if (r < gridRows-1 && oldGrid[r+1][c] && !oldGrid[r+1][c]->getState())
				dirVec.push_back(Direction::EATDOWN);
			if (c > 0 && !grid[r][c-1] && oldGrid[r][c-1] && !oldGrid[r][c-1]->getState())
				dirVec.push_back(Direction::EATLEFT);
		}

		//Doodlebug moves without eating
		//Check if there's a DB in the new grid in the desired space
		//This wont need to check oldGrid for ants because they would have
		//been detected in the above block
		if (dirVec.empty() && crit->getState()) {
			if (r > 0 && !grid[r-1][c])
				dirVec.push_back(Direction::UP);
			if (c < gridCols-1 && !grid[r][c+1])
				dirVec.push_back(Direction::RIGHT);
			if (r < gridRows-1 && !grid[r+1][c])
				dirVec.push_back(Direction::DOWN);
			if (c > 0 && !grid[r][c-1])
				dirVec.push_back(Direction::LEFT);
		//Ant moves (must account for doodlebug moves)
		} else if (dirVec.empty() && !crit->getState()) {
			if (r > 0 && !grid[r-1][c])
				dirVec.push_back(Direction::UP);
			if (c < gridCols-1 && !grid[r][c+1] && !oldGrid[r][c+1])
				dirVec.push_back(Direction::RIGHT);
			if (r < gridRows-1 && !grid[r+1][c] && !oldGrid[r+1][c])
				dirVec.push_back(Direction::DOWN);
			if (c > 0 && !grid[r][c-1])
				dirVec.push_back(Direction::LEFT);
		}

	//Directions available during breeding
	} else if (crit && breedCall) {
		if (r > 0 && !grid[r-1][c])
			dirVec.push_back(Direction::UP);
		if (c < gridCols-1 && !grid[r][c+1])
			dirVec.push_back(Direction::RIGHT);
		if (r < gridRows-1 && !grid[r+1][c])
			dirVec.push_back(Direction::DOWN);
		if (c > 0 && !grid[r][c-1])
			dirVec.push_back(Direction::LEFT);
	}
	
	//If the critter can't move or breed anywhere
	if (dirVec.empty()) { return Direction::NONE; }

	//Return a random pre-approved direction
	return (dirVec[rand() % dirVec.size()]);
}

void Game::printGrid() {
	printHorizontalBorder(2*gridCols+2, '_');
	for (int i = 0; i < gridRows ; ++i) {
		cout << setw(2) << left << "|";
		for (int j = 0 ; j < gridCols ; ++j) {
			//Empty spaces
			if (!grid[i][j]) { 
				cout << setw(2) << left << " ";
			//Ants
			} else if (!grid[i][j]->getState()) {
				cout << setw(2) << left << "O";
			//Doodlebugs
			} else if (grid[i][j]->getState()) {
				cout << setw(2) << left << "X";
			}
		}
		cout << setw(2) << left << "|" << endl;
	}
	printHorizontalBorder(2*gridCols+2, '_');
}
