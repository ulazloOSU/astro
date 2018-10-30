/*
 * critter.cpp
 */

#include "critter.hpp"

//Overloaded constructor
Critter::Critter(int row, int col, int critSteps, int lastBreed, int state) {
	this->row = row;
	this->col = col;
	this->critSteps = critSteps;
	this->lastBreed = lastBreed;
	this->state = state;
}
