//
//  MapItemBase.cpp
//  MatchPuzzleRPGT
//
//

#include "MapItemBase.h"

MapItemBase::MapItemBase():
x(-1),
y(-1)
{
    
}

MapItemBase::~MapItemBase()
{
    
}

int MapItemBase::getX()
{
    return x;
}

int MapItemBase::getY()
{
    return y;
}

MapItemType MapItemBase::getType()
{
    return type;
}