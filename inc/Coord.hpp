#ifndef COORD_HPP
#define COORD_HPP

#include <iostream>

struct Coord {

    Coord() : x(0), y(0)
    { }

    Coord(int x_, int y_) : x(x_), y(y_)
    { }

    Coord(const Coord& orig) : x(orig.x), y(orig.y)
    { }

    ~Coord() {}

    Coord& operator=(const Coord& orig)
    {
        if (this != &orig)
        {
            x = orig.x;
            y = orig.y;
        }
        return *this;
    }

    Coord& operator+(const Coord& value)
    {
        x += value.x;
        y += value.y;
        return (*this);
    }

    bool operator <(const Coord& value)
    {
        return (x + y < value.x + value.y);
    }

    bool operator >(const Coord& value)
    {
        return (x + y > value.x + value.y);
    }

    bool operator==(const Coord& value)
    {
        return (x == value.x && y == value.y);
    }

    std::ostream& dump(std::ostream& stream) {
        stream << "x " << x << " y " << y << std::endl;
        return stream;
    }

    int x;
    int y;
};

#endif // COORD_HPP
