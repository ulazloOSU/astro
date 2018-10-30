/*
 * ant.hpp
 */

#ifndef ANT_HPP
#define ANT_HPP

#include "critter.hpp"

class Ant : public Critter {
	private:

	protected:

	public:
		Ant(int row, int col, int critSteps = 0, int lastBreed = 0, int state = 0) 
		: Critter(row, col, critSteps, lastBreed, state) {};
		~Ant();
		virtual Critter* move(Direction dir) override;
		virtual Critter* breed(Direction dir) override;
};

#endif
