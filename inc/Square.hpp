/* 
 * File:   Square.hpp
 * Author: fancel
 *
 * Created on May 5, 2011, 12:19 PM
 */

#ifndef SQUARE_HPP
#define	SQUARE_HPP

#include "Types.hpp"

#define PLAYER(x)       (0x0000000F & x)
#define IS_TAKABLE(x)   (0x000000F0 & (x << 4))
#define HORZ(x)         (0x00000F00 & (x << 8))
#define VERT(x)         (0x0000F000 & (x << 12))
#define DIAGL(x)        (0x000F0000 & (x << 16))
#define DIAGR(x)        (0x00F00000 & (x << 20))

#define GET_PLAYER(x)      (x & 0x0000000F)
#define GET_TAKABLE(x)     ((x & 0x000000F0) >> 4)
#define GET_HORZ(x)        ((x & 0x00000F00) >> 8)
#define GET_VERT(x)        ((x & 0x0000F000) >> 12)
#define GET_DIAGL(x)       ((x & 0x000F0000) >> 16)
#define GET_DIAGR(x)       ((x & 0x00F00000) >> 20)
#define GET_HORZ_BLOCK(x) ((x & 0x03000000) >> 24)
#define GET_VERT_BLOCK(x) ((x & 0x0C000000) >> 26)
#define GET_DIAGL_BLOCK(x) ((x & 0x30000000) >> 28)
#define GET_DIAGR_BLOCK(x) ((x & 0xC0000000) >> 30)

class Square {

public:
    struct Data{
        unsigned short player : 4;
        unsigned short is_takable : 4;
        unsigned short horz : 4;
        unsigned short vert : 4;
        unsigned short diagl : 4;
        unsigned short diagr : 4;
        unsigned short horz_block : 2;
        unsigned short vert_block : 2;
        unsigned short diagl_block : 2;
        unsigned short diagr_block : 2;
    };
    
public:
    Square();
    virtual ~Square();

    int32_t             getRawData() const;
    void                setRawData(int32_t mask);
    void                dumpData() const;

    inline Data & getData() {
      return (*reinterpret_cast<Square::Data *>(&_data));
    }

    inline const Data & getData() const {
      return (*reinterpret_cast<const Square::Data *>(&_data));
    }

    inline void setData(Data & data) {
        _data = (int32_t)(*reinterpret_cast<int32_t*>(&data));
    }

    inline void setVert(unsigned int lineSize) {
        getData().vert = lineSize;
    }

    inline void setHorz(unsigned int lineSize) {
        getData().horz = lineSize;
    }

    inline void setDiagl(unsigned int lineSize) {
        getData().diagl = lineSize;
    }

    inline void setDiagr(unsigned int lineSize) {
        getData().diagr = lineSize;
    }

    inline void setIsTackable(bool value) {
        getData().is_takable = value;
    }

    inline void setPlayer(unsigned int player) {
        getData().player = player;
    }

    inline void setHorzBlock(unsigned int endBlock) {
        getData().horz_block = endBlock;
    }

    inline void setVertBlock(unsigned int endBlock) {
        getData().vert_block = endBlock;
    }

    inline void setDiaglBlock(unsigned int endBlock) {
        getData().diagl_block = endBlock;
    }

    inline void setDiagrBlock(unsigned int endBlock) {
        getData().diagr_block = endBlock;
    }

    inline unsigned int getHorz() const {
        return GET_HORZ(_data);
    }

    inline unsigned int getVert() const {
        return GET_VERT(_data);
    }

    inline unsigned int getDiagl() const {
        return GET_DIAGL(_data);
    }

    inline unsigned int getDiagr() const {
        return GET_DIAGR(_data);
    }

    inline unsigned int getHorzBlock() const {
        return getData().horz_block;
    }

    inline unsigned int getVertBlock() const {
        return getData().vert_block;
    }

    inline unsigned int getDiaglBlock() const {
        return getData().diagl_block;
    }

    inline unsigned int getPlayer() const {
        return getData().player;
    }

    inline unsigned int getDiagrBlock() const {
        return getData().diagr_block;
    }

    inline bool getIsTakable() const {
        return getData().is_takable;
    }
    
private:
     int32_t _data;
};

#endif	/* SQUARE_HPP */

