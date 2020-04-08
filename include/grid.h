#ifndef _grid_h
#define _grid_h

/*
* project:	peak_finder
* file:		grid.h
* author:	en2
* date:		07-04-2020
*/

#include "node.h"
#include <vector>
#include <algorithm>

enum class List : unsigned char
{
    OPENED,
    CLOSED
}; /* enum: List */

class Grid
{
    struct Move {int dx; int dy;};
    static constexpr Move moves[] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};

public:
    Grid(int size);
    ~Grid();

    void normalize();

    Node * at(int x, int y);
    Node * random();
    Node * neighbour(Node * parent, int which);

    void to(List list, Node * node);
    Node * from(List list);

protected:
    float _find_min();
    float _find_max();

    bool _not_present_on(std::vector<std::pair<Node *, float>> & list, Node * node);
    void _sort(std::vector<std::pair<Node *, float>> & list);

private:
    Node ** _node;
    int _size;

    std::vector<std::pair<Node *, float>> _opened;
    std::vector<std::pair<Node *, float>> _closed;

}; /* class: Grid */


#endif /* define: grid_h */