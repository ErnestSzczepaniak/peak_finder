#ifndef _block_h
#define _block_h

/*
* project:	peak_finder
* file:		block.h
* author:	en2
* date:		06-04-2020
*/

static constexpr auto size_block = 10;

struct Position
{
    int x;
    int y;
}; /* structure: Position */

struct Size
{
    int x;
    int y;
}; /* structure: Size */


struct Color
{
    int r;
    int g;
    int b;
}; /* structure: Color */


class Block
{
public:
    Block();
    ~Block();

    Block & draw();
    Block & clear();

    Block & value(float value);
    float value();

    Block & position(int x, int y);
    Position position();
    Position grid();

    Block & size(int x, int y);
    Size size();

    Block & color(int r, int g, int b);
    Color color();

    

private:
    float _value;
    Size _size;
    Position _position;
    Color _color_current;
    Color _color_stored;

}; /* class: Block */

void block_remove_dc(Block ** block, int number);
void block_normalise(Block ** block, int number);
Block ** block_init(int number, float freq, int depth, int seed);
Block * block_start(Block ** block, int number);

#endif /* define: block_h */