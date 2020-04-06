#include "block.h"
#include "display.h"


Block::Block()
{

}

Block::~Block()
{

}

Block & Block::draw()
{
    d_color(_color.r, _color.g, _color.b);
    d_square(_position.x, _position.y, _size.x - 1, _size.y - 1);

    return *this;
}

Block & Block::clear()
{

    return *this;
}

Block & Block::value(double value)
{
    _value = value;

    if (_value > 0.0) color((_value * 255.0), 0, 0);
    else color(0, 0, (_value * 255.0));
    return *this;
}

double Block::value()
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
    _color = {r, g, b};

    return *this;
}

Color Block::color()
{
    return _color;
}
