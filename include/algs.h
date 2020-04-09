#ifndef _climb_h
#define _climb_h

/**
 * @file	climb.h
 * @author	Radoslaw Krupka
 * @date	07-04-2020
 * @brief	
 * @details	
**/

#include "grid.h"

struct Result
{
    int steps;
    Node * peak;
}; /* structure: Result */


Result climb(Grid * grid, Node * current, int number);
Result greedy(Grid * grid, Node * current, int number);

#endif /* define: climb_h */