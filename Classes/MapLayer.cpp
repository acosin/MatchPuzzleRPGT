//
//  MapLayer.cpp
//  MatchPuzzleRPGT
//
//

#include "MapLayer.h"

MapLayer::MapLayer():
_tileMap(nullptr),
_background(nullptr)
{
    
}

MapLayer::~MapLayer()
{
    
}

bool MapLayer::init()
{
    if (Layer::init()==false) {
        return false;
    }
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    
    
    return true;
}

bool MapLayer::initMap(const std::string &mapFilename)
{
    _tileMap = TMXTiledMap::create(mapFilename);
    _background = _tileMap->getLayer("Background");
    
    addChild(_tileMap);
    setContentSize(_tileMap->getContentSize());
    
    return true;
}

MapLayer* MapLayer::create(const std::string &mapFilename)
{
    MapLayer* map = MapLayer::create();
    map->initMap(mapFilename);
    return map;
}