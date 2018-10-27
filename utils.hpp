/*********************************************************************
**                          utils.hpp                               **
** These utilities are a continually growing compilation of reusable**
** pieces of code I've found useful. See the descriptions for each  **
** individual function to see what they do.                         **
*********************************************************************/

#ifndef UTILS_HPP
#define UTILS_HPP

#include <climits>
#include <string>
using std::string;

bool floatCheck(string &str, float &retFloat, float MIN_NUM, float MAX_NUM, bool canEqlMin = 0, bool canEqlMax = 0);
bool intCheck(string &str, int &retInt, int MIN_NUM = INT_MIN, int MAX_NUM = INT_MAX, bool canEqlMin = 0, bool canEqlMax = 0);
bool yesOrNo(string qn);
void printHorizontalBorder(int width = 40, char spacer = '=');

#endif
