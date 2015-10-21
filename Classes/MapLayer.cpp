//
//  MapLayer.cpp
//  MatchPuzzleRPGT
//
//

#include "MapLayer.h"

MapLayer::MapLayer():
_tileMap(nullptr),
_background(nullptr),
_player(nullptr)
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

bool MapLayer::initMap(const std::string &mapFilename, const std::string &playerFilename)
{
    _tileMap = TMXTiledMap::create(mapFilename);
    _background = _tileMap->getLayer("Background");
    addChild(_tileMap);
    setContentSize(_tileMap->getContentSize());
    
    
    TMXObjectGroup *objects = _tileMap->getObjectGroup("Objects");
    CCASSERT(objects!=nullptr, "'Objects' object group not found");
    auto spawnPoint = objects->getObject("SpawnPoint");
    CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
    int x = spawnPoint["x"].asInt();
    int y = spawnPoint["y"].asInt();
    _player = Sprite::create(playerFilename);
    _player->setPosition(x, y);
    addChild(_player);
    //setViewPointCenter(_player->getPosition());
    
    return true;
}

MapLayer* MapLayer::create(const std::string &mapFilename, const std::string &playerFilename)
{
    MapLayer* map = MapLayer::create();
    map->initMap(mapFilename, playerFilename);
    return map;
}

void MapLayer::setViewPointCenter(Point position)
{
    auto winSize = Director::getInstance()->getWinSize();
    
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
    auto actualPosition = Point(x, y);
    
    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
    auto viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);
}

void MapLayer::movePlayerTo(int x, int y)
{
    //TODO
}
