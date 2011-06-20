#ifndef REFEREEMANAGER_HPP
#define REFEREEMANAGER_HPP

/*
  paramettre qui geree l'ensemble des Referee
*/

#include <map>

#include "Coord.hpp"
#include "Singleton.hpp"
#include "Square.hpp"

class RefereeManager : public Singleton<RefereeManager>
{
    SINGLETON_CLASS(RefereeManager);

public:
    typedef void (Square::*setDirFunc)(unsigned int);
    typedef unsigned int (Square::*getDirFunc)() const;

    enum Vector {
        NONE,
        RIGHT,
        UP_RIGHT,
        UP,
        UP_LEFT,
        LEFT,
        DOWN_LEFT,
        DOWN,
        DOWN_RIGHT
    };

    struct DirInfo {

        DirInfo(const Vector& inv, const Coord& dir, setDirFunc set, getDirFunc get)
        : invert(inv), direction(dir), setter(set), getter(get)
        {
            //std::cout << "DirInfo x " << direction.x << " y " << direction.y << std::endl;
        }

        DirInfo()
        : invert(NONE), direction(Coord(0, 0)), setter(0), getter(0)
        {}

        Vector invert;
        Coord direction;
        setDirFunc setter;
        getDirFunc getter;
    };

    typedef std::map<Vector, DirInfo> DirMap;

    unsigned int size() const;
    bool fivePrize() const;
    bool doubleThree() const;
    void setFivePrize(bool value);
    void setDoubleThree(bool value);
    DirMap& map();
    bool goTo(unsigned int boardSize, unsigned int& x, unsigned int& y, Vector dir);
    unsigned int getDirAlign(const Square& square, Vector dir) const;
    void setDirAlign(Square& square, Vector dir, unsigned int lineSize) const;

private:
    DirMap _directionMap;
    unsigned int _mapSize;
    bool _fivePrize;
    bool _doubleThree;

    RefereeManager();
    RefereeManager(const RefereeManager& orig);

    inline bool checkPosition(unsigned int x, unsigned int y, unsigned int size) {
        return (x < size && y < size);
    }
};

#endif // REFEREEMANAGER_HPP
