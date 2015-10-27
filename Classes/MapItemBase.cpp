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

MapItemBase::MapItemBase(int x, int y, bool mavable, MapItemType type, const std::string &imagePath)
{
    setX(x);
    setY(y);
    setMovable(movable);
    setType(type);
    setImagePath(imagePath);
}

MapItemBase::~MapItemBase()
{
    
}

uint32_t MapItemBase::getID()
{
    return id;
}

void MapItemBase::setID(uint32_t id)
{
    this->id = id;
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

std::string MapItemBase::getImagePath()
{
    return imagePath;
}

void MapItemBase::setImagePath(const std::string &path)
{
    imagePath = path;
}

/*
Sprite* MapItemBase::getSprite()
{
    return sprite;
}

void MapItemBase::setSprite(Sprite* sprite)
{
    this->sprite = sprite;
}
*/

Node* MapItemBase::getNode()
{
    return node;
}

void MapItemBase::setNode(cocos2d::Node *node)
{
    this->node = node;
}