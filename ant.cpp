/*
 * ant.cpp
 */

#include <iostream> //For access to NULL
#include "critter.hpp"
#include "ant.hpp"

Critter* Ant::move(Direction dir) {
	Critter* crit = NULL;

	//Increment tracker variables
	++this->critSteps;
	++this->lastBreed;

	//Create a new DB in the specified direction
	switch(dir) {
		case (Direction::UP) : {
			crit = new Ant(this->row-1, this->col,
						   this->critSteps, this->lastBreed);
			//std::cout << "Ant moved up." << std::endl;
			break;
		}
		case (Direction::RIGHT) : {
			crit = new Ant(this->row, this->col+1,
						   this->critSteps, this->lastBreed);
			//std::cout << "Ant moved right." << std::endl;
			break;
		}
		case (Direction::DOWN) : {
			crit = new Ant(this->row+1, this->col,
						   this->critSteps, this->lastBreed);
			//std::cout << "Ant moved down." << std::endl;
			break;
		}
		case (Direction::LEFT) : {
			crit = new Ant(this->row, this->col-1,
						   this->critSteps, this->lastBreed);
			//std::cout << "Ant moved left." << std::endl;
			break;
		}
		case (Direction::NONE) : {
			crit = new Ant(this->row, this->col,
						   this->critSteps, this->lastBreed);
			//std::cout << "Ant didnt move." << std::endl;
			break;
		}
	}
	return crit;
}

//Will return NULL if breed would be out of bounds
Critter* Ant::breed(Direction dir) {
	Critter* crit = NULL;
	//Only breed if more than 3 steps since last breed
	if (this->lastBreed >= 3) {
		//Breed a new critter in the specified direction 
		switch(dir) {
			case (Direction::UP) :
				this->lastBreed = 0;
				crit = new Ant(row-1, col);
				//std::cout << "Ant bred up." << std::endl;
				break;

			case (Direction::RIGHT) :
				this->lastBreed = 0;
				crit = new Ant(row, col+1);
				//std::cout << "Ant bred right." << std::endl;
				break;

			case (Direction::DOWN) :
				this->lastBreed = 0;
				crit = new Ant(row+1, col);
				//std::cout << "Ant bred down." << std::endl;
				break;

			case (Direction::LEFT) :
				this->lastBreed = 0;
				crit = new Ant(row, col-1);
				//std::cout << "Ant bred left." << std::endl;
				break;

			//Don't reset breed counter
			case (Direction::NONE) :
				break;
		}
	}
	return crit;
}
