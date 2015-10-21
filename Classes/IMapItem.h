//
//  IMapItem.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum class MapItemType {
    Player,
    Enemy,
    Other,
    
    count
};

class IMapItem
{
public:
    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual void setX(int x) = 0;
    virtual void setY(int y) = 0;
    virtual void setXY(int x, int y) = 0;
    virtual MapItemType getType() = 0;
    virtual void setType(MapItemType type) = 0;
    virtual bool isMovable() = 0;
    virtual void setMovable(bool flag) = 0;
};
