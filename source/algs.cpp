#include "algs.h"
#include "display.h"

Result climb(Grid * grid, Node * current, int number)
{
    int steps = 0;

    while(1)
    {
        current->blank();

        grid->to(List::OPENED, current);

        for (int i = 0; i < 8; i++)
        {
            if (auto * neighbour = grid->neighbour(current, i); neighbour != nullptr)
            {
                grid->to(List::OPENED, neighbour);
                neighbour->as_known();

                d_sleep(20);
            }
        }
        
        auto * candidate = grid->from(List::OPENED);

        candidate->blink(50);

        while(auto * visited = grid->from(List::OPENED));

        if (candidate == current) break;
        else current = candidate;

        steps++;
    }

    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            grid->at(i, j)->as_known();
            d_sleep(1);
        }
    }

    current->blink(200);
    current->blink(200);

    return {steps, current};
}

Result greedy(Grid * grid, Node * current, int number)
{
    int steps = 0;

    current->as_known();
    grid->to(List::OPENED, current);

    while(1)
    {
        current = grid->from(List::OPENED);

        grid->to(List::CLOSED, current);

        if (current->value() == 1.0f) break;

        for (int i = 0; i < 8; i++)
        {
            if (auto * neighbour = grid->neighbour(current, i); neighbour != nullptr)
            {
                grid->to(List::OPENED, neighbour);
                neighbour->as_known();

                d_sleep(1);
            }
        }

        steps++;
    }

    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            grid->at(i, j)->as_known();
            d_sleep(1);
        }
    }

    current->blink(200);
    current->blink(200);

    return {steps, current};
}