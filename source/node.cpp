#include "node.h"
#include "display.h"

Node::Node()
{

}

Node::~Node()
{

}

void Node::value(float value)
{
    _value = value;
}

float Node::value()
{
    return _value;
}

void Node::as_unknown()
{
    auto [r, g, b] = _restore();
    int top = 60;

    r = (r * top) / 10;
    if (r > 255) r = 255;

    g = (g * top) / 10;
    if (g > 255) g = 255;

    b = (b * top) / 10;
    if (b > 255) b = 255;

    _draw({r, g, b});
}

void Node::as_known()
{
    auto color = _restore();

    _draw(color);
}

void Node::blink(int sleep)
{
    auto [r, g, b] = _restore();

    for (int i = 0; i < 3; i++)
    {
        _draw({0, 255, 0});
        d_sleep(sleep);
        _draw({r, g, b});
        d_sleep(sleep);
    }
}

void Node::blank()
{
    _draw({0, 0, 0});
}

void Node::position(int x, int y)
{
    _position = {x, y};
}

Node::Position Node::position()
{
    return _position;
}

//---------------------------------------------| info |---------------------------------------------//

void Node::_draw(Color color)
{
    d_color(color.r, color.g, color.b);
    d_square(_position.x * size, _position.y * size, size - 1, size - 1);

    d_flush();
}

Node::Color Node::_restore()
{
    int r = 0, g = 0, b = 0;

    if (_value > 0.5)
    {
        r = _value * 255;
        g = (1 - _value) * 255 * 2;
    } 
    if (_value < 0.5)
    {
        b = (1 - _value) * 255;
        g = _value * 255 * 2;
    }

    return {r, g, b};
}