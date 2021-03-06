/* 
 * File:   Referee.cpp
 * Author: fancel
 *
 * Created on May 5, 2011, 1:14 PM
 */

#include <iostream>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/foreach.hpp>

#include "Board.hpp"
#include "Referee.hpp"
#include "Game.hpp"

Referee::Referee(Board& board)
: _actionStack(), _winLineList(), _board(board), _threeChecker(_board), _score(0), _winner(0) {
}

Referee::Referee(const Referee& orig)
: _actionStack(orig._actionStack), _winLineList(orig._winLineList), _board(orig._board), _threeChecker(_board), _score(orig._score), _winner(orig._winner) {
}

Referee::Referee(const Referee& orig, Board& board)
: _actionStack(orig._actionStack), _winLineList(orig._winLineList), _board(board), _threeChecker(_board), _score(orig._score), _winner(orig._winner) {
}

Referee::~Referee() {
}

void Referee::setScore(unsigned int player, unsigned int value) {
    _score[player & 1] = value;
}

unsigned int Referee::getScore(unsigned int player) const {
    return _score[player & 1];
}

bool Referee::DoAction(const UniqueAction& action) {
    bool result = true;

    BOOST_FOREACH(const RockPlayed& item, action) {
        if (item._act == PLACED) {
            result = result && PlaceRock(item._pos, item._playerId);
        } else if (item._act == TAKEN) {
            result = result && TakeRock(item._pos);
        }
    }

    for (unsigned int i = 0; i < _score.size(); i++) {
        _score[i] += action._score[i];
    }
    return result;
}

bool Referee::UndoAction(const UniqueAction& action) {
    bool result = true;

    BOOST_FOREACH(const RockPlayed& item, action) {
        if (item._act == PLACED) {
            result = result && TakeRock(item._pos);
        } else if (item._act == TAKEN) {
            result = result && PlaceRock(item._pos, item._playerId);
        }
    }
    for (unsigned int i = 0; i < _score.size(); i++) {
//        std::cout << "score " << _score[i] << " action " << action._score[i] << std::endl;
        _score[i] -= action._score[i];
    }
    _winner = 0;
    return result;
}

bool Referee::UndoLastAction() {
    bool result = false;
    if (_actionStack.size()) {
        if (UndoAction(_actionStack.top())) {
            _actionStack.pop();
            result = true;
        }
    }
    return result;
}

bool Referee::TakeRock(const Coord& pos) {
    bool result = false;
    if (_board(pos).getPlayer()) {
        _board(pos).setRawData(0);
        fpropagation_inverse(pos.x, pos.y);
        result = true;
    }
    return result;
}

bool Referee::PlaceRock(const Coord& pos, const unsigned int player) {
    bool result = false;
    if (testPosition(pos.x, pos.y, player)) {
        _board(pos).setPlayer(player);
        fpropagation(pos.x, pos.y, player);
        result = true;
    }
    return result;
}

void Referee::dumpScore() const {
    std::cout << "player " << 1 << " " << getScore(1) << std::endl;
    std::cout << "player " << 2 << " " << getScore(2) << std::endl;
}

/**
 * deplace x et y dans la direction choisie
 */
bool Referee::goTo(unsigned int& x, unsigned int& y, RefereeManager::Vector dir) const {
    return RefereeManager::Instance().goTo(_board.getSize(), x, y, dir);
}

unsigned int Referee::getDirAlign(const Square& square, RefereeManager::Vector dir) const {
    return RefereeManager::Instance().getDirAlign(square, dir);
}

void Referee::setDirAlign(Square& square, RefereeManager::Vector dir, unsigned int lineSize) {
    RefereeManager::Instance().setDirAlign(square, dir, lineSize);
}

unsigned int Referee::getDirEnd(const Square& square, RefereeManager::Vector dir) const {
    return Singleton<RefereeManager>::Instance().getDirEnd(square, dir);
}

void Referee::setDirEnd(Square& square, RefereeManager::Vector dir, unsigned int endValue) {
    Singleton<RefereeManager>::Instance().setDirEnd(square, dir, endValue);
}

/*
 * Teste si la case fait partie d'au moins un alignement superieur ou egale a 'size'
 */
bool Referee::ispartOfAlign(const Square& value, unsigned int size) {
    //value.dumpData();
    unsigned int diagl = value.getDiagl();
    unsigned int diagr = value.getDiagr();
    unsigned int horz = value.getHorz();
    unsigned int vert = value.getVert();

    if (diagl >= size || diagr >= size || horz >= size || vert >= size) {
        return true;
    }
    return false;
}

/*
 * Teste si la case fait partie d'au moins un alignement de 'size'
 */
bool Referee::ispartOfExactAlign(const Square& value, unsigned int size) {
    return (value.getDiagl() == size ||
            value.getDiagr() == size ||
            value.getHorz() == size ||
            value.getVert() == size);
}

void Referee::setRaw(Square& value, unsigned int val) {
    value.setRawData(val);
}

/**
 * get de l'atribut qui contient le gagnant
 */
unsigned int Referee::checkWin() const {
    return _winner;
}

/**
 * reset le gagnant
 */
void Referee::reset() {
    _winner = 0;
}

/**
 * Tente de placer une pierre
 */
int Referee::tryPlaceRock(unsigned int x, unsigned int y, unsigned int player) {
    int value = -1;

    if (testPosition(x, y, player)) {
        UniqueAction action;
        _board(x, y).setPlayer(player);
        action.push_back(RockPlayed(PLACED, player, Coord(x, y)));
        fpropagation(x, y, player);
        value = checkPrize(x, y, player, action);
        if (value) {
            setScore(player, getScore(player) + value * 2);
            action._score[player & 1] = value * 2;
        }

        checkWin(x, y, player);
        _actionStack.push(action);
    }
    return value;
}

/**
 * Determine si la position est valide pour une nouvelle pierre
 */
bool Referee::testPosition(unsigned int x, unsigned int y, unsigned int player) {
    bool value = false;

    if (_board.checkSize(x, y) && _board(x, y).getPlayer() == 0) {
        value = true;
        if (Singleton<RefereeManager>::Instance().doubleThree())
            value = checkDoubleThree(x, y, player);
    }
    return value;
}

/**
 * cherche dans toute les directions si il a des pierre a prendre
 */
unsigned int Referee::checkPrize(unsigned int x, unsigned int y, unsigned int player, ActionArray& action) {
    unsigned int result = 0;
    const RefereeManager::VectorArray& dir = RefereeManager::Instance().getVectorArray();

    for (unsigned int i = 1; i < dir.size(); i++) {
        if (checkPrize_dir(x, y, dir[i], player)) {
            cleanRock(x, y, dir[i], action);
            result++;
        }
    }

    return result;
}

/**
 * cherche si il y a une prise dans une direction
 */
bool Referee::checkPrize_dir(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player) const {
    if (checkCanTake(x, y, dir, player)) {
        goTo(x, y, dir);
        //std::cout << x << ", " << y << " is takable" << std::endl;
        _board(x, y).setIsTackable(true);

        goTo(x, y, dir);
        //std::cout << x << ", " << y << " is takable" << std::endl;
        _board(x, y).setIsTackable(true);

        if (goTo(x, y, dir) && _board(x, y).getPlayer() == player)
            return true;
    }
    return false;
}

/**
 * check si les pions dans la direction sont prenable par le joueurs player
 */

bool Referee::checkCanTake(unsigned x, unsigned int y, RefereeManager::Vector dir, unsigned int player) const {
    return (goTo(x, y, dir) && _board(x, y).getPlayer() == Referee::opponant(player) &&
            goTo(x, y, dir) && _board(x, y).getPlayer() == Referee::opponant(player) &&
            goTo(x, y, dir) && _board(x, y).getPlayer() != Referee::opponant(player));
}

/**
 * clean les pierre trouver comme prise
 */
void Referee::cleanRock(unsigned int x, unsigned int y, RefereeManager::Vector dir, ActionArray& action) {
    //std::cout << "cleanRock" << std::endl;
    unsigned int xtmp, ytmp;

    goTo(x, y, dir);
    action.push_back(RockPlayed(TAKEN, _board(x, y).getPlayer(), Coord(x, y)));
    setRaw(_board(x, y), 0);

    xtmp = x;
    ytmp = y;

    goTo(x, y, dir);
    action.push_back(RockPlayed(TAKEN, _board(x, y).getPlayer(), Coord(x, y)));
    setRaw(_board(x, y), 0);

    fpropagation_inverse(xtmp, ytmp);
    fpropagation_inverse(x, y);
}

bool Referee::checkIsTakable(unsigned int x, unsigned int y) {
    unsigned int player = _board(x, y).getPlayer();
    //std::cout << x << ", " << y << " is not takable" << std::endl;
    _board(x, y).setIsTackable(false);
    if (ispartOfExactAlign(_board(x, y), 2)) {
        const RefereeManager::VectorArray& dir = RefereeManager::Instance().getVectorArray();

        for (unsigned int i = 1; i < dir.size(); ++i) {
            if (checkIsTakable(x, y, dir[i], player)) {
                unsigned int xtmp = x;
                unsigned int ytmp = y;
                //std::cout << x << ", " << y << " is takable" << std::endl;
                _board(x, y).setIsTackable(true);
                goTo(xtmp, ytmp, dir[i]);
                //std::cout << xtmp << ", " << ytmp << " is takable" << std::endl;
                _board(xtmp, ytmp).setIsTackable(true);
            }
        }
    }
    return _board(x, y).getIsTakable();
}

bool Referee::checkIsTakable(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player) const {
    unsigned int xinv = x;
    unsigned int yinv = y;

    return (getDirAlign(_board(x, y), dir) == 2 && goTo(xinv, yinv, RefereeManager::Instance().invert(dir)) && goTo(x, y, dir) && goTo(x, y, dir) &&
            ((_board(xinv, yinv).getPlayer() == Referee::opponant(player) || _board(x, y).getPlayer() == Referee::opponant(player)) &&
            !(_board(xinv, yinv).getPlayer() == Referee::opponant(player) && _board(x, y).getPlayer() == Referee::opponant(player))));
}

/**
 * Determine si le coup est gagnant
 */

void Referee::checkWin(unsigned int x, unsigned int y, unsigned int player) {
    if (getScore(player) >= 10)
        _winner = player;
    else if (ispartOfAlign(_board(x, y), 5)) {
        _winLineList.push_back(Coord(x, y));
        checkWinList();
        //if (_winner)
        //  _board.DumpBoard();
    }
}

void Referee::checkWinList() {
    WinList::iterator it = _winLineList.begin();
    WinList::iterator ite = _winLineList.end();

    while (!_winner && it != ite && _board(it->x, it->y).getPlayer() && ispartOfAlign(_board(it->x, it->y), 5)) {
        if (RefereeManager::Instance().fivePrize()) {
            if (checkFivePrize(it->x, it->y))
                _winner = _board(it->x, it->y).getPlayer();
        } else {
            _winner = _board(it->x, it->y).getPlayer();
        }
        ++it;
    }
    if (!_winner && it != ite) {
        _winLineList.erase(it);
        checkWinList();
    }
    if (_winner) {
        _winLineList.clear();
    }
}

/**
 * Fonction de test de la regle speciale des 5 pions lors d'une tentative de victoire
 */
bool Referee::checkFivePrize(unsigned int x, unsigned int y) {
    unsigned int player = _board(x, y).getPlayer();
    bool result = false;

    if (player) {
        if (_board(x, y).getDiagl() > 4) {
            unsigned int size = checkFivePrize(x, y, RefereeManager::UP_LEFT, player);
            size += checkFivePrize(x, y, RefereeManager::DOWN_RIGHT, player);
            size++;
            if (size >= 5)
                result = true;
        }

        if (_board(x, y).getDiagr() > 4 && !result) {
            unsigned int size = checkFivePrize(x, y, RefereeManager::UP_RIGHT, player);
            size += checkFivePrize(x, y, RefereeManager::DOWN_LEFT, player);
            size++;
            if (size >= 5)
                result = true;
        }

        if (_board(x, y).getHorz() > 4 && !result) {
            unsigned int size = checkFivePrize(x, y, RefereeManager::RIGHT, player);
            size += checkFivePrize(x, y, RefereeManager::LEFT, player);
            size++;
            if (size >= 5)
                result = true;
        }

        if (_board(x, y).getVert() > 4 && !result) {
            unsigned int size = checkFivePrize(x, y, RefereeManager::UP, player);
            size += checkFivePrize(x, y, RefereeManager::DOWN, player);
            size++;
            if (size >= 5)
                result = true;
        }
    }

    return result;
}

unsigned int Referee::checkFivePrize(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player) {
    int cleanRock = 0;

    while (goTo(x, y, dir) && _board(x, y).getPlayer() == player && !checkIsTakable(x, y)) {
        cleanRock++;
    }
    return cleanRock;
}

/**
 * Get/Set pour les regles speciales
 */
bool Referee::doubleThree() const {
    return RefereeManager::Instance().doubleThree();
}

bool Referee::doubleThree(bool value) {
    RefereeManager::Instance().setDoubleThree(value);
    return RefereeManager::Instance().doubleThree();
}

bool Referee::fivePrize() const {
    return RefereeManager::Instance().fivePrize();
}

bool Referee::fivePrize(bool value) {
    RefereeManager::Instance().setFivePrize(value);
    return RefereeManager::Instance().fivePrize();
}

/*
 * Fonction de test de la regle speciale des double 3 pions align
 */
bool Referee::checkDoubleThree(unsigned int x, unsigned int y, unsigned int player) {
    return _threeChecker.CheckDoubleThree(x, y, player);
}

/* Try to propagate in EVERY directions */

void Referee::fpropagation(unsigned int x, unsigned int y, const unsigned int player) {
    boost::thread_group threadGroup;

    threadGroup.create_thread(
            boost::bind(&Referee::fpropagation_dir, this, x, y, RefereeManager::UP, player)
            );
    threadGroup.create_thread(
            boost::bind(&Referee::fpropagation_dir, this, x, y, RefereeManager::LEFT, player)
            );
    threadGroup.create_thread(
            boost::bind(&Referee::fpropagation_dir, this, x, y, RefereeManager::UP_RIGHT, player)
            );
    threadGroup.create_thread(
            boost::bind(&Referee::fpropagation_dir, this, x, y, RefereeManager::UP_LEFT, player)
            );

    checkIsTakable(x, y);
    threadGroup.join_all();
}

void Referee::fpropagation_dir(unsigned int x, unsigned int y, RefereeManager::Vector dir, const unsigned int player) {
    PropagationInfo info;

    info = flineSize(x, y, dir, player) + flineSize(x, y, RefereeManager::Instance().invert(dir), player);
    info.lineSize += 1;
    setDirAlign(_board(x, y), dir, info.lineSize);
    setDirEnd(_board(x, y), dir, info.endBlock);

    fsetline(x, y, dir, player, info);
    fsetline(x, y, RefereeManager::Instance().invert(dir), player, info);
}

void Referee::fpropagation_inverse(unsigned int x, unsigned int y) {
    //std::cout << "propagation inverse" << std::endl;
    const RefereeManager::VectorArray& dir = RefereeManager::Instance().getVectorArray();
    boost::thread_group threadGroup;

    for (unsigned int i = 1; i < dir.size(); i++) {
        threadGroup.create_thread(boost::bind(&Referee::fpropag_inverse_to, this, x, y, dir[i]));
        //fpropag_inverse_to(x, y, dir[i]);
    }
    threadGroup.join_all();
}

void Referee::fpropag_inverse_to(unsigned int x, unsigned int y, Vector dir) {
    if (goTo(x, y, dir)) {
        unsigned int player = _board(x, y).getPlayer();
        if (player) {
            fpropagation(x, y, player);
        }
    }
}

Referee::PropagationInfo Referee::flineSize(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    PropagationInfo info;

    while (goTo(x, y, dir) && _board(x, y).getPlayer() == player)
        info.lineSize++;
    if (_board(x, y).getPlayer() != Referee::opponant(player)) {
        info.endBlock++;
    }

    if (info.lineSize == 0 && _board(x, y).getPlayer() == Referee::opponant(player)) {
        unsigned int opponant_end = getDirEnd(_board(x, y), dir);
        opponant_end--;
        setDirEnd(_board(x, y), dir, opponant_end);
        while (goTo(x, y, dir) && _board(x, y).getPlayer() == Referee::opponant(player))
            setDirEnd(_board(x, y), dir, opponant_end);
    }

    return info;
}

void Referee::fsetline(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player, const PropagationInfo& value) {
    while (goTo(x, y, dir) && _board(x, y).getPlayer() == player) {
        setDirAlign(_board(x, y), dir, value.lineSize);
        setDirEnd(_board(x, y), dir, value.endBlock);
        checkIsTakable(x, y);
    }
}

void Referee::dumpSquare(unsigned int x, unsigned int y) const {
    std::cout << "###########" << std::endl;
    std::cout << "x = " << x << " y= " << y << std::endl;
    std::cout << "player " << GET_PLAYER(_board(x, y).getRawData()) << std::endl;
    std::cout << "takable ";
    if (GET_TAKABLE(_board(x, y).getRawData()))
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
    std::cout << "align horz " << _board(x, y).getHorz() << std::endl;
    std::cout << "align vert " << _board(x, y).getVert() << std::endl;
    std::cout << "align DiagL " << _board(x, y).getDiagl() << std::endl;
    std::cout << "align DiagR " << _board(x, y).getDiagr() << std::endl;
    std::cout << "###########" << std::endl;
}

void Referee::dumpDirection(unsigned int x, unsigned int y, RefereeManager::Vector dir) const {
    while (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) != 0)
        dumpSquare(x, y);
}

void Referee::dumpPropagation(unsigned int x, unsigned int y) const {
    const RefereeManager::VectorArray& dir = RefereeManager::Instance().getVectorArray();

    dumpSquare(x, y);
    for (unsigned int i = 1; i < dir.size(); i++) {
        dumpDirection(x, y, dir[i]);
    }
}
