//
//  MapLayer.cpp
//  MatchPuzzleRPGT
//
//

#include "MapLayer.h"

const std::string MapLayer::EventNameMapTounch = "EventNameMapTounch";

MapLayer::MapLayer():
_tileMap(nullptr),
_background(nullptr),
_player(nullptr),
_meta(nullptr)
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
    
    return initMap(mapFilename) && initPlayer(playerFilename);
}


bool MapLayer::initMap(const std::string &mapFilename)
{
    _tileMap = TMXTiledMap::create(mapFilename);
    if (_tileMap == nullptr) {
        return false;
    }
    
    _background = _tileMap->getLayer("Background");
    _meta = _tileMap->getLayer("meta");
    _meta->setVisible(false);
    addChild(_tileMap);
    setContentSize(_tileMap->getContentSize());
    
    // handle event
    // TODO: modify later
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool { return true; };
    listener->onTouchEnded = CC_CALLBACK_2(MapLayer::onTouchEnded, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

// TODO: remove later
bool MapLayer::initPlayer(const std::string &playerFilename)
{
    TMXObjectGroup *objects = _tileMap->getObjectGroup("Objects");
    CCASSERT(objects!=nullptr, "'Objects' object group not found");
    
    auto spawnPoint = objects->getObject("SpawnPoint");
    CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
    int x = spawnPoint["x"].asInt();
    int y = spawnPoint["y"].asInt();
    //TODO: set by StageData in GameStageController
    _player = Sprite::create(playerFilename);
    _player->setPosition(x, y);
    addChild(_player);
    
    return true;
}

void MapLayer::initPlayer(cocos2d::Sprite *player)
{
    CCASSERT(_player==nullptr, "MapLayer::initPlayer: _player != nullptr");
    _player = player;
    addChild(_player);
}


MapLayer* MapLayer::create(const std::string &mapFilename, const std::string &playerFilename)
{
    MapLayer* map = MapLayer::create();
    map->initMap(mapFilename, playerFilename);
 
    return map;
}

MapLayer* MapLayer::create(const std::string &mapFilename)
{
    MapLayer* map = MapLayer::create();
    map->initMap(mapFilename);
    
    return map;
}


Vec2 MapLayer::convertToPixelPos(const Vec2 &mapPos)
{
    auto ret = _background->getPositionAt(mapPos);
    return ret;
}

Vec2 MapLayer::convertToMapPos(const Vec2 &pixelPos)
{
    auto x = (int)(pixelPos.x / _tileMap->getTileSize().width);
    auto y = (int)(_tileMap->getMapSize().height)- (int)(pixelPos.y / _tileMap->getTileSize().height) - 1;
    
    return Vec2(x,y);
}

void MapLayer::scaleAsTileSize(Node* node)
{
    auto tileSize = _tileMap->getTileSize();
    auto size = node->getContentSize();
    //TODO: may need 0 divide check
    node->setScale(tileSize.width/size.width, tileSize.height/size.height);
}

bool MapLayer::isGoalPos(int x, int y)
{
    auto tileGid = _meta->getTileGIDAt(Vec2(x,y));
    if (tileGid != 0) {
        auto propertiesDict = _tileMap->getPropertiesForGID(tileGid).asValueMap();
        auto prop = propertiesDict["isGoal"];
        if (prop.asString().compare("true") == 0) {
            return true;
        }
    }
    return false;
}

void MapLayer::enableTouch()
{
    this->setTouchEnabled(true);
}

void MapLayer::disableTouch()
{
    this->setTouchEnabled(false);
}

// -- private --

bool MapLayer::moveNodeOnMap(Node* node, int x, int y)
{
    if (node == nullptr) {
        return false;
    }
    
    auto pixelPos = convertToPixelPos(Vec2(x,y));
    //TODO: should check boundary condiiton
    node->setPosition(pixelPos);
    
    return true;
}

/*
bool MapLayer::moveSpriteOnMap(Sprite* sprite, int x, int y)
{
    if (sprite == nullptr) {
        return false;
    }
    
    auto pixelPos = convertToPixelPos(Vec2(x,y));
    //TODO: should check boundary condiiton
    sprite->setPosition(pixelPos);
    
    return true;
}
*/

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

// here only do the visulaization
// TODO: may modify or remote later (only use moveX/moveY)
bool MapLayer::movePlayerTo(int x, int y)
{
    if (_player == nullptr) {
        return false;
    }
    if(moveNodeOnMap(_player, x, y)) {
        return true;
    } else {
        //TODO: may need more process here
        return false;
    }
}

void MapLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    auto touchLocation = touch->getLocation();
    touchLocation = this->convertToNodeSpace(touchLocation);
    
    Point mapPos = convertToMapPos(touchLocation);
    if (mapPos.x < 0 || mapPos.y < 0 ||
        mapPos.x >= _tileMap->getMapSize().width ||
        mapPos.y >= _tileMap->getMapSize().height) {
        CCLOG("touch out of map");
        return;
    }
    CCLOG("touch map: %f,%f", mapPos.x, mapPos.y);
    dispatchEventMapTouch(mapPos);
}

void MapLayer::dispatchEventMapTouch(Point &mapPos)
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(MapLayer::EventNameMapTounch, &mapPos);
}