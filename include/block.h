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

    Block & value(double value);
    double value();

    Block & position(int x, int y);
    Position position();

    Block & size(int x, int y);
    Size size();

    Block & color(int r, int g, int b);
    Color color();

private:
    double _value;
    Size _size;
    Position _position;
    Color _color;

}; /* class: Block */


#endif /* define: block_h */