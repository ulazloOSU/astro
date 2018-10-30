/*
 * game.hpp
 */

#ifndef GAME_HPP
#define GAME_HPP

#include "critter.hpp"

//NOTE: Max grid size will be 99x99, min grid size will be
//based on the number of doodlebugs+ants 

class Game {
	private:
		int userSteps, 
			gridRows, 
			gridCols, 
			startNumAnts, 
			startNumDB;

		Critter*** oldGrid;
		Critter*** grid;

	protected:

	public:
		Game();
//		~Game();
		void createGrid(Critter*** &newGrid);	
		void deleteGrid(Critter*** &delGrid);
		void populateGrid(Critter*** &tmp);
		void runSim();
		void move();
		void breed();
		void starve();
		Direction dirSelect(Critter* &crit, bool breedCall = false);
		void printGrid();
		
		//Get and Set functions
		int getSteps() { return this->userSteps; } 
		int getGridRows() { return this->gridRows; }
		int getGridCols() { return this->gridCols; }
		int getStartNumAnts() { return this->startNumAnts; }
		int getStartNumDB() { return this->startNumDB; }
		void setSteps(int steps) { this->userSteps = steps; }
		void setGridRows(int gridRows) { this->gridRows = gridRows; }
		void setGridCols(int gridCols) { this->gridCols = gridCols; }
		void setStartNumAnts(int startNumAnts) { this->startNumAnts = startNumAnts; }
		void setStartNumDB(int startNumDB) { this->startNumDB = startNumDB; }
};

#endif
