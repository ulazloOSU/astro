/*
 * db.cpp
 */

#include <iostream> //For access to NULL
#include "critter.hpp"
#include "db.hpp"

Critter* DB::move(Direction dir) {
	Critter* crit = NULL;

	//Increment tracker variables
	++this->critSteps;
	++this->lastBreed;
	++this->state;

	//Create a new DB in the specified direction
	switch(dir) {
		//DBs state gets reset to 1 (by default) because it ate
		case (Direction::EATUP) :
			//std::cout << "Doodlebug ate up." << std::endl;
			crit = new DB(this->row-1, this->col,
						  this->critSteps, this->lastBreed,1);
			break;

		case (Direction::EATRIGHT) :
			//std::cout << "Doodlebug ate right." << std::endl;
			crit = new DB(this->row, this->col+1,
						  this->critSteps, this->lastBreed,1);
			break;

		case (Direction::EATDOWN) :
			//std::cout << "Doodlebug ate down." << std::endl;
			crit = new DB(this->row+1, this->col,
						  this->critSteps, this->lastBreed,1);
			break;

		case (Direction::EATLEFT) :
			//std::cout << "Doodlebug ate left." << std::endl;
			crit = new DB(this->row, this->col-1,
						  this->critSteps, this->lastBreed,1);
			break;

		//Pass on the current DBs state since DB didnt eat
		case (Direction::UP) :
			crit = new DB(this->row-1, this->col,
						  this->critSteps, this->lastBreed,
						  this->state);
			break;

		case (Direction::RIGHT) :
			crit = new DB(this->row, this->col+1,
						  this->critSteps, this->lastBreed,
						  this->state);
			break;

		case (Direction::DOWN) :
			crit = new DB(this->row+1, this->col,
						  this->critSteps, this->lastBreed,
						  this->state);
			break;

		case (Direction::LEFT) :
			crit = new DB(this->row, this->col-1,
						  this->critSteps, this->lastBreed,
						  this->state);
			break;

		case (Direction::NONE) :
			crit = new DB(this->row, this->col,
						  this->critSteps, this->lastBreed,
						  this->state);
			break;
	}
	return crit;
}

//Will return NULL if breed would be out of bounds
Critter* DB::breed(Direction dir) {
	Critter* crit = NULL;
	//Only breed if more than 8 steps since last breed
	if (this->lastBreed >= 8) {
		//Breed a new critter in the specified direction
		switch(dir) {
			case (Direction::UP) :
				this->lastBreed = 0;
				crit = new DB(row-1, col);
				break;

			case (Direction::RIGHT) :
				this->lastBreed = 0;
				crit = new DB(row, col+1);
				break;

			case (Direction::DOWN) :
				this->lastBreed = 0;
				crit = new DB(row+1, col);
				break;

			case (Direction::LEFT) :
				this->lastBreed = 0;
				crit = new DB(row, col-1);
				break;

			//Don't reset breed counter 
			case (Direction::NONE) :
				break;
		}
	} 
	return crit;
}
