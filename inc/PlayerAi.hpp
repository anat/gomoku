#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include <vector>
#include <set>

#include "Board.hpp"
#include "APlayer.hpp"

template < typename IHeuristic, typename ISearchCase >
class PlayerAi : public APlayer {
public:
    typedef typename IHeuristic::HeuristicValue HeuristicValue;
    typedef typename ISearchCase::CoordContainer CoordContainer;
    typedef typename std::map< HeuristicValue, Coord > FinalContainer;

    PlayerAi(unsigned int id) : APlayer(id), _heuristic(), _maxDepth(3), _alpha(), _beta() {
    }

    PlayerAi(const PlayerAi& orig) {
        this->operator =(orig);
    }

    ~PlayerAi() {
    }

    PlayerAi & operator=(const PlayerAi& orig) {
        if (this != &orig) {
            _heuristic = orig._heuristic;
        }
        return *this;
    }

    bool doAction(Board& gameboard, Referee& ref, int , int ) {
        //HeuristicValue originValue = _heuristic(gameboard, this->getPlayerNum());
        _alpha = HeuristicValue();
        _beta = HeuristicValue();

        CoordContainer possibleCase;

        _searchCase(gameboard, possibleCase);

        typename CoordContainer::iterator it = possibleCase.begin();
        typename CoordContainer::iterator ite = possibleCase.end();
        FinalContainer finalContainer;

        Board copy;
        //HeuristicValue heufinal;

        while (it != ite) {
            copy = gameboard;
            Referee refcopy(ref, copy);
            if (refcopy.tryPlaceRock(it->x, it->y, this->getPlayerNum()) > -1) {

                //heufinal = min(1, copy, refcopy, );
                //std::cout << "heu " << heufinal << std::endl;
                finalContainer[_heuristic(copy, this->getPlayerNum(), it->x, it->y)] = *it;
            }
            ++it;
        }

        typename FinalContainer::reverse_iterator final = finalContainer.rbegin();


        if (final != finalContainer.rend()) {
            std::cout << "final heu " << final->first << std::endl;
            ref.tryPlaceRock(final->second.x, final->second.y, this->getPlayerNum());
        }

        return true;
    }

    HeuristicValue min(unsigned int depth, Board& origin, Referee& reforigin, HeuristicValue boardHeuristic) {
        //std::cout << "min" << std::endl;
        //if (depth > _maxDepth || reforigin.checkWin() != 0)
        //  return boardHeuristic;

        CoordContainer possibleCase;

        _searchCase(origin, possibleCase);

        typename CoordContainer::const_iterator it = possibleCase.begin();
        typename CoordContainer::const_iterator ite = possibleCase.end();

        HeuristicValue heucopy = HeuristicValue();
        HeuristicValue heuResult = HeuristicValue();
        HeuristicValue result = HeuristicValue();
        Board copy;

        while (it != ite) {
            copy = origin;
            Referee refcopy(reforigin, copy);
            if (refcopy.tryPlaceRock(it->x, it->y, this->getPlayerNum()) > -1) {
                heucopy = _heuristic(copy, this->getPlayerNum(), it->x, it->y);
                heuResult = max(depth + 1, copy, refcopy, heucopy);
                if (heuResult > result)
                    result = heuResult;
            }
            ++it;
        }

        return result;
    }

    HeuristicValue max(unsigned int depth, Board& origin, Referee& reforigin, HeuristicValue boardHeuristic) {
        //std::cout << "max" << std::endl;

        if (depth > _maxDepth || reforigin.checkWin() != 0) {
            return boardHeuristic;
        }

        CoordContainer possibleCase;

        _searchCase(origin, possibleCase);

        typename CoordContainer::const_iterator it = possibleCase.begin();
        typename CoordContainer::const_iterator ite = possibleCase.end();

        HeuristicValue heucopy = HeuristicValue();
        HeuristicValue heuResult = HeuristicValue();
        HeuristicValue result = HeuristicValue();
        Board copy;

        while (it != ite) {
            copy = origin;
            Referee refcopy(reforigin);
            if (refcopy.tryPlaceRock(it->x, it->y, this->getPlayerNum()) > -1) {
                heucopy = _heuristic(copy, this->getPlayerNum(), it->x, it->y);
                heuResult = min(depth + 1, copy, refcopy, heucopy);
                if (heuResult > result)
                    result = heuResult;
            }
            ++it;
        }

        return result;
    }
private:
    IHeuristic _heuristic;
    ISearchCase _searchCase;
    unsigned int _maxDepth;
    HeuristicValue _alpha;
    HeuristicValue _beta;
};

#endif // PLAYERAI_HPP
