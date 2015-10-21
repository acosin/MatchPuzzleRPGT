//
//  MapItemBase.cpp
//  MatchPuzzleRPGT
//
//

#include "MapItemBase.h"

MapItemBase::MapItemBase():
x(-1),
y(-1),
movable(false)
{
    
}

MapItemBase::MapItemBase(int x, int y, bool mavable, MapItemType type)
{
    setX(x);
    setY(y);
    setMovable(movable);
    setType(type);
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

void MapItemBase::setX(int x)
{
    this->x = x;
}

void MapItemBase::setY(int y)
{
    this->y = y;
}

void MapItemBase::setXY(int x, int y)
{
    setX(x);
    setY(y);
}

bool MapItemBase::isMovable()
{
    return movable;
}

void MapItemBase::setMovable(bool flag)
{
    movable = flag;
}

MapItemType MapItemBase::getType()
{
    return type;
}

void MapItemBase::setType(MapItemType type)
{
    this->type = type;
}