

#include "display.h"
#include "grid.h"
#include "generator.h"
#include <map>
#include "algs.h"


int main(int argc, char * argv[])
{
    int number = 50;

    d_open(number * 10, number * 10, "finder");

    Grid grid(number);
    Generator generator(0.05, 4, 568);

    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            grid.at(i, j)->value(generator.at(i, j));
        }
    }

    grid.normalize();

    auto * current = grid.random();

    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            grid.at(i, j)->as_unknown();
        }
    }

    //---------------------------------------------| info |---------------------------------------------//

    //auto steps = climb(&grid, current, number);
    auto steps = greedy(&grid, current, number);
    
    d_close();
}
