/*
 * critter.hpp
 */

#ifndef CRITTER_HPP
#define CRITTER_HPP

enum class Direction { NONE = 0, 
					   UP, 
					   RIGHT, 
					   DOWN, 
					   LEFT, 
					   EATUP,
					   EATRIGHT,
					   EATDOWN,
					   EATLEFT };

class Critter {
	private:

	protected:
		int row, 
			col, 
			critSteps, 
			lastBreed,
			state;
			// 0 = ant
			// 1 = DB
			// 2 = DB that hasn't eaten for 1 day
			// 3 = DB that hasn't eaten for 2 days
			// 4 = DB that hasn't eaten for 3 days
		bool hasMoved;

	public:
		Critter(int row, int col, int critSteps = 0, int lastBreed = 0, int state = 0);
		virtual ~Critter();
		virtual Critter* move(Direction dir) = 0;
		virtual Critter* breed(Direction dir) = 0;
		int getRow() { return this->row; }
		int getCol() { return this->col; }
		void setRow(int row) { this->row = row; }
		void setCol(int col) { this->col = col; }
		int getState() { return state; }
		bool getHasMoved() {return hasMoved; }
		void setHasMoved(bool hasMoved) {this->hasMoved = hasMoved; }
};
#endif
