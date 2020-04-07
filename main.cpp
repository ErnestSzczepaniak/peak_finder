#include "block.h"
#include "stdlib.h"
#include "display.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"


struct Move
{
    int dx;
    int dy;
}; /* structure: Move */

Move moves[] = 
{
    {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}
};

bool is_valid(int number, int x, int y, int move)
{
    auto change = moves[move];
    auto next_x = x + change.dx;
    auto next_y = y + change.dy;

    if ((next_x >= 0) && (next_x < number))
    {
        if ((next_y >= 0) && (next_y < number)) return true;
    }

    return false;
}

Block * near(Block ** block, int number, int x, int y, int move)
{
    if (is_valid(number, x, y, move))
    {
        return &block[x + moves[move].dx][y + moves[move].dy];
    }
    else return nullptr;
}

int min_index(float * tab, int size)
{
    int index;
    float value = 100.0f;

    for (int i = 0; i < size; i++)
    {
        if (tab[i] < value)
        {
            value = tab[i];
            index = i;
        }
    }
    
    return index;
}

float min(float * tab, int size)
{
    float value = 100.0f;

    for (int i = 0; i < size; i++)
    {
        if (tab[i] < value)
        {
            value = tab[i];
        }
    }
    
    return value; 
}

int main(int argc, char * argv[])
{
    int number = 50;
    auto ** block = block_init(number, 0.02, 3, 5);
    auto * current = block_start(block, number);

    /* ---------------------------------------------| info |--------------------------------------------- */

    while(1)
    {
        Color ccol, ncol[8];
        float h[8];

        ccol = current->color();
        current->color(255, 255, 255);

        for (int i = 0; i < 8; i++)
        {
            if (auto * next = near(block, number, current->grid().x, current->grid().y, i); next != nullptr)
            {
                ncol[i] = next->color();

                next->color(50, 50, 50);

                d_sleep(10);

                h[i] = 1 - next->value();
            }
            else h[i] = 100.0f;
        }

        if (1 - current->value() > min(h, 8)) // better path found
        {
            auto index = min_index(h, 8);

            auto * next = near(block, number, current->grid().x, current->grid().y, index);

            for (int i = 0; i < 2; i++)
            {
                next->color(0, 255, 0);
                d_sleep(15);
                next->color(50, 50, 50);
                d_sleep(15);
            }
            
            for (int i = 0; i < 8; i++)
            {
                if (auto * next = near(block, number, current->grid().x, current->grid().y, i); next != nullptr)
                {
                    next->color(ncol[i].r - 10, ncol[i].g - 10, ncol[i].b - 10);
                }
            }
            
            current->color(ccol.r, ccol.g, ccol.b);

            current = near(block, number, current->grid().x, current->grid().y, index);
        }
        else
        {
            for (int i = 0; i < 10; i++)
            {
                current->color(0, 255, 0);
                d_sleep(15);
                current->color(50, 50, 50);
                d_sleep(15);
            }

            break;
        }
        
    }

    for (int i = 0; i < number; i++)
    {
        delete[] block[i];
    }
    
    delete[] block;



    d_close();

}
