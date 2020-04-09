

#include "display.h"
#include "grid.h"
#include "generator.h"
#include <map>
#include "algs.h"
#include "string.h"

int main(int argc, char * argv[])
{
    auto number = atoi(argv[1]);
    auto seed = atoi(argv[2]);
    const char * alg = argv[3];

    d_open(number * 10, number * 10, "finder");

    Grid grid(number);
    Generator generator(0.05, 4, seed);

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

    Result result;

    if (strcmp(alg, "greedy") == 0)
    {
        result = greedy(&grid, current, number);
    }
    else if (strcmp(alg, "climb") == 0)
    {
        result = climb(&grid, current, number);
    }   
    
    printf("Simulation finished !\n");
    printf("Algorithm: %s\n", alg);
    printf("Peak found @ [%d, %d]\n", result.peak->position().x, result.peak->position().y);
    printf("Peak value: %1.4f\n", result.peak->value());
    printf("Steps: %d\n", result.steps);
    
    d_close();
}
