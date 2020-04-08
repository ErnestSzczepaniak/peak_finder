#ifndef _node_h
#define _node_h

/*
* project:	peak_finder
* file:		node.h
* author:	en2
* date:		07-04-2020
*/

class Node
{
    struct Color {int r; int g; int b;};
    struct Position {int x; int y;};

    static constexpr auto size = 10;

public:
    Node();
    ~Node();

    void value(float value);
    float value();

    void as_unknown();
    void as_known();
    void blink(int sleep);
    void blank();

    void position(int x, int y);
    Position position();

protected:
    void _draw(Color color);

    Color _restore();

private:
    float _value;
    Position _position;

}; /* class: Node */


#endif /* define: node_h */