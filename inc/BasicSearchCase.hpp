/* 
 * File:   BasicSearchCase.hpp
 * Author: fancel
 *
 * Created on June 16, 2011, 10:50 AM
 */

#ifndef BASICSEARCHCASE_HPP
#define	BASICSEARCHCASE_HPP

#include <vector>
#include <deque>

#include "ISearchCase.hpp"
#include "Coord.hpp"

class BasicSearchCase : public ISearchCase< std::deque<Coord> >
{
public:
    void operator()(const Board& game, CoordContainer& possibleCase);
    void Dump(const CoordContainer&) const;
private:
    bool hasPlayerAround_simple(const Board& game, unsigned int x, unsigned int y);
    bool hasPlayerAround_double(const Board& game, unsigned int x, unsigned int y);
};

#endif	/* BASICSEARCHCASE_HPP */

