//
//  MapItemBase.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "IMapItem.h"

USING_NS_CC;

class MapItemBase : public IMapItem
{
protected:
    int x;
    int y;
    MapItemType type;
    
public:
    MapItemBase();
    ~MapItemBase();
    
    int getX() override;
    int getY() override;
    MapItemType getType() override;
};
