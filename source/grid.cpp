#include "grid.h"
#include "time.h"
#include "stdlib.h"

Grid::Grid(int size) : _size(size)
{
    _node = new Node *[_size];

    for (int i = 0; i < _size; i++)
    {
        _node[i] = new Node[_size];
    }

    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            at(i, j)->position(i, j);
        }
    }
}

Node * Grid::random()
{
    srand(time(nullptr));

    auto x = rand() % _size;
    auto y = rand() % _size;

    return at(x, y);
}

Node * Grid::neighbour(Node * parent, int which)
{
    auto next_x = parent->position().x + moves[which].dx;
    auto next_y = parent->position().y + moves[which].dy;

    if ((next_x >= 0) && (next_x < _size) && (next_y >= 0) && (next_y < _size))
    {
        return at(next_x, next_y);
    }
    else return nullptr;
}

void Grid::to(List list, Node * node)
{
    if (_not_present_on(_closed, node) && _not_present_on(_opened, node))
    {
        if (list == List::OPENED)
        {
            _opened.push_back(std::make_pair(node, 1.0f - node->value()));
            _sort(_opened);
        } 
        else if (list == List::CLOSED) _closed.push_back(std::make_pair(node, 1.0f - node->value()));
    }
}

Node * Grid::from(List list)
{
    if (list == List::OPENED)
    {
        if (_opened.size() > 0)
        {
            auto item = _opened.front();
            _opened.erase(_opened.begin());
            return item.first;
        }
        else return nullptr;
    }
    else if (list == List::CLOSED)
    {
        if (_closed.size() > 0)
        {
            auto item = _closed.front();
            _closed.erase(_closed.begin());
            return item.first;
        }
        else return nullptr;
    }
    return nullptr;
}

Grid::~Grid()
{
    for (int i = 0; i < _size; i++)
    {
        delete[] _node[i];
    }
    
    delete[] _node;
}

void Grid::normalize()
{
    auto min = _find_min();

    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            at(i, j)->value(at(i, j)->value() - min);
        }
    }
    
    auto max = _find_max();

    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            at(i, j)->value(at(i, j)->value() / max);
        }
    }

    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            at(i, j)->value(at(i, j)->value() * at(i, j)->value());
        }
    }
}

Node * Grid::at(int x, int y)
{
    return &_node[x][y];
}

float Grid::_find_min()
{
    auto min = 100.0f;

    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            if (at(i, j)->value() < min) min = at(i, j)->value();
        }
    }
    
    return min;
}

float Grid::_find_max()
{
    auto max = 0.0f;

    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            if (at(i, j)->value() > max) max = at(i, j)->value();
        }
    }
    
    return max;
}

bool Grid::_not_present_on(std::vector<std::pair<Node *, float>> & list, Node * node)
{
    auto present = [&](std::pair<Node *, float> & element){return (element.first == node);};

    auto iterator = std::find_if(list.begin(), list.end(), present);

    return (iterator == list.end());
}

void Grid::_sort(std::vector<std::pair<Node *, float>> & list)
{
    auto sort = [](std::pair<Node * , float> & first, std::pair<Node * , float> & second){return (first.second < second.second);};

    std::sort(list.begin(), list.end(), sort);
}