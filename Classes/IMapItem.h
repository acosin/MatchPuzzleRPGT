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
    virtual int getX();
    virtual int getY();
    virtual MapItemType getType();
};
