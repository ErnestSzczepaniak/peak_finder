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

int climb(Grid * grid, Node * current, int number);
int greedy(Grid * grid, Node * current, int number);

#endif /* define: climb_h */