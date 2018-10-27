/*
 * db.hpp
 * db = doodlebug
 */

#ifndef DB_HPP
#define DB_HPP

#include "critter.hpp"

class DB : public Critter {
	private:

	protected:

	public:
		DB(int row, int col, int critSteps = 0, int lastBreed = 0, int state = 1) 
		: Critter(row, col, critSteps, lastBreed, state) {};
		virtual Critter* move(Direction dir) override;
		virtual Critter* breed(Direction dir) override;
};

#endif
