#include "block.h"
#include "display.h"
#include "math.h"
#include "perlin.h"
#include "time.h"
#include "stdlib.h"

Block::Block()
{

}

Block::~Block()
{

}

Block & Block::draw()
{
    d_color(_color_current.r, _color_current.g, _color_current.b);
    d_square(_position.x, _position.y, _size.x - 1, _size.y - 1);

    d_flush();

    return *this;
}

Block & Block::clear()
{

    return *this;
}

Block & Block::value(float value)
{
    _value = value;

    int r = 0, g = 0, b = 0;

    if (value > 0.5)
    {
        r = value * 255;
        g = (1 - value) * 255 * 2;
    } 
    if (value < 0.5)
    {
        b = (1 - value) * 255;
        g = value * 255 * 2;
    } 

    _color_current = {r, g, b};

    return *this;
}

float Block::value()
{
    return _value;
}

Block & Block::position(int x, int y)
{
    _position = {x, y};

    return *this;
}

Position Block::position()
{
    return _position;
}

Position Block::grid()
{
    return {_position.x / size_block, _position.y / size_block};
}

Block & Block::size(int x, int y)
{
    _size = {x, y};

    return *this;
}

Size Block::size()
{
    return _size;
}

Block & Block::color(int r, int g, int b)
{
    _color_current = {r, g, b};

    draw();

    return *this;
}

Color Block::color()
{
    return _color_current;
}

void block_remove_dc(Block ** block, int number)
{
    float min = 10e5;

    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            auto value = block[i][j].value();
            if (value < min) min = value;
        }
    }
    
    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            block[i][j].value(block[i][j].value() - min);
        }
    }
}

void block_normalise(Block ** block, int number)
{
    float max = 0.0f;

    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            auto value = block[i][j].value();
            if (value > max) max = value;
        }
    }
    
    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            block[i][j].value(block[i][j].value() / max);
        }
    }
}

Block ** block_init(int number, float freq, int depth, int seed)
{
    auto * block = new Block *[number];
    for (int i = 0; i < number; i++)
    {
        block[i] = new Block[number];
    }

    d_open(number * size_block, number * size_block, "finder");

    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            block[i][j].value(perlin2d(i, j, freq, depth, seed));
            block[i][j].size(size_block, size_block);
            block[i][j].position(i * size_block, j * size_block);
        }   
    }
    
    block_remove_dc(block, number);
    block_normalise(block, number);

    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            block[i][j].draw();
        }
    }

    d_flush();

    return block;
}

Block * block_start(Block ** block, int number)
{
    srand(time(nullptr));
    auto x = rand() % number;
    auto y = rand() % number;

    auto * current = &block[x][y];
}