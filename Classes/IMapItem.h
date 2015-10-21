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
    virtual MapItemType getType() = 0;
};
