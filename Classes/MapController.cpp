//
//  MapController.cpp
//  MatchPuzzleRPGT
//
//

#include "MapController.h"

MapController::MapController(StageData *stageData)
{
    _IDpool_mapItem = new IDPool();
    initMap(stageData);
}

MapController::~MapController()
{
    CC_SAFE_DELETE(_IDpool_mapItem);
    CC_SAFE_DELETE(_mapLayer);
}

bool MapController::initMap(StageData *stageData)
{
    if (stageData == nullptr) {
        return false;
    }
    
    _stageData = stageData;
    
    createMapLayerFromData();
    CC_ASSERT(_mapLayer != nullptr);
    
    //createEnemies();
    createEnemiesDebug();
    
    return true;
}

MapLayer* MapController::getMapLayer()
{
    return _mapLayer;
}


int MapController::getPlayerX()
{
    return _playerItem->getX();
}

int MapController::getPlayerY()
{
    return _playerItem->getY();
}


void MapController::movePlayerTo(int x, int y)
{
    _lastPlayerX = _playerItem->getX();
    _lastPlayerY = _playerItem->getY();
    
    _playerItem->setXY(x, y);
    // TODO: may update rendering
    auto sprite = _playerItem->getSprite();
    _mapLayer->moveSpriteOnMap(sprite, x, y);
}

bool MapController::tryMovePlayerTo(int x, int y)
{
    CC_ASSERT(_IDpool_mapItem != nullptr);
    if (x<0 || y<0 ||x>= _stageData->_mapWidth || y>=_stageData->_mapHeight) {
        //CCLOG("(%d,%d) out of map", x,y);
        return false;
    }
    
    if (findMapItems(x, y).size() != 0) {
        CCLOG("already exist item in (%d,%d)", x,y);
        return false;
    }
    
    movePlayerTo(x, y);
    return true;
}


bool MapController::tryMovePlayerUp()
{
    auto x = _playerItem->getX();
    auto y = _playerItem->getY();
    return tryMovePlayerTo(x, y-1);
}
bool MapController::tryMovePlayerDown()
{
    auto x = _playerItem->getX();
    auto y = _playerItem->getY();
    return tryMovePlayerTo(x, y+1);
}
bool MapController::tryMovePlayerLeft()
{
    auto x = _playerItem->getX();
    auto y = _playerItem->getY();
    return tryMovePlayerTo(x-1, y);
}
bool MapController::tryMovePlayerRight()
{
    auto x = _playerItem->getX();
    auto y = _playerItem->getY();
    return tryMovePlayerTo(x+1, y);
}


MapLayer* MapController::createMapLayerFromData()
{
    CC_ASSERT(_stageData != nullptr);
    auto mapFilename = StageData::getMapTMXFilename(0); //TODO: get from _stageData
    //auto mapFilename = StageData::getMapTMXFilename(_stageData->_mapID); //TODO: get from _stageData
    auto playerFilename = "Player_on_map.png"; //TODO: get from _playerItem // remove
    
    //_mapLayer = MapLayer::create(mapFilename, playerFilename);
    _mapLayer = MapLayer::create(mapFilename);
    //createPlayerItem(2, 3, playerFilename);
    //TODO: should get this from StageData
    createPlayerItem(_stageData->_playerInitialX, _stageData->_playerInitialY, playerFilename);
    //createPlayerItem(2, 2, playerFilename);
    
    return _mapLayer;
}


bool MapController::moveMapItemTo(uint32_t id, int x, int y)
{
    CC_ASSERT(_IDpool_mapItem != nullptr);
    if (!_IDpool_mapItem->exist(id)) {
        return false;
    }
    
    auto item = _mapItems[id];
    //TODO: may need animation
    item->setXY(x, y);
    auto sprite = item->getSprite();
    _mapLayer->moveSpriteOnMap(sprite, x, y);
    
    
    return true;
}

//
bool MapController::tryMoveMapItemTo(uint32_t id, int x, int y)
{
    CC_ASSERT(_IDpool_mapItem != nullptr);
    if (findMapItems(x, y).size() != 0) {
        CCLOG("already exist item in (%d,%d)", x,y);
        return false;
    }
    return moveMapItemTo(id, x, y);
}

std::vector<uint32_t> MapController::findMapItems(int x, int y)
{
    std::vector<uint32_t> itemIDs;
    // TODO: may need to consider the traversal speed
    for (auto item : _mapItems) {
        if (item.second->getX() == x && item.second->getY() == y) {
            itemIDs.push_back(item.second->getID());
        }
    }
    return itemIDs;
}

bool MapController::removeMapItem(uint32_t id)
{
    bool ret = false;
    
    if (_IDpool_mapItem->exist(id)) {
        _mapItems.erase(id);
        _IDpool_mapItem->removeID(id);
        ret = true;
    }
    
    return ret;
}


bool MapController::removeMapItem(IMapItem* pItem)
{
    if (pItem == nullptr)
        return false;
    return removeMapItem(pItem->getID());
}



bool MapController::createPlayerItem(int x, int y, const std::string &imagePath)
{
    CC_ASSERT(_mapLayer != nullptr);
    
    _playerItem = new MapItemPlayer(x, y, imagePath);
    auto id = _IDpool_mapItem->generateID();
    _playerItem->setID(id);
    auto sprite = Sprite::create(imagePath);
    //change this to pixel coordinate
    sprite->setPosition(_mapLayer->convertToPixelPos(Vec2(x,y)));
    _playerItem->setSprite(sprite);
    _mapLayer->initPlayer(sprite);
    
    return true;
}


uint32_t MapController::createEnemyItem(int x, int y, const std::string &imagePath)
{
    uint32_t id = 0;
    
    if (_mapLayer == nullptr) {
        return 0;
    }
    
    auto enemy = new MapItemEnemy(x,y,imagePath);
    id = _IDpool_mapItem->generateID();
    enemy->setID(id);
    //TODO: set data later
    //enemy->setStatusData(<#EnemyStatusData *statusData#>);
    auto sprite = Sprite::create(imagePath);
    //change this to pixel coordinate
    sprite->setPosition(_mapLayer->convertToPixelPos(Vec2(x,y)));
    enemy->setSprite(sprite);    _mapItems[id] = enemy;
    //TODO: scale enemy item here, may remove later (image should be ideal size)
    _mapLayer->scaleAsTileSize(sprite);
    _mapLayer->addChild(sprite);
    
    return id;
}

// -- private --


//NOTE: not used
/*
std::map<uint32_t, MapItemEnemy*>::iterator MapController::findMapItem(uint32_t id)
{
    std::map<uint32_t, MapItemEnemy*>::iterator it;
    for (it = _mapItems.begin(); it != _mapItems.end(); it++) {
        if ((*it).second->getID() == id) {
            return it;
        }
    }
    return it;
}

std::map<uint32_t, MapItemEnemy*>::iterator MapController::findMapItem(IMapItem* ptr)
{
    return find(_mapItems.begin(), _mapItems.end(), ptr);
}
*/
void MapController::createEnemies()
{
    
}

void MapController::createEnemiesDebug()
{
    //TODO: should create every enemy from csv/json data later
    EnemyStatusData* data;
    
    data = new EnemyStatusData(0,    // enemyID,
                               "element_0.png",   //iconPath,
                               //std::string imagePath,
                               "EnemyName_0",     //enemyName,
                               ElementType::RED,  //type,
                               0,    //level,
                               10,   //hp,
                               1     //atk
                               );
    //createEnemyItem(1,2,data->getSpriteImagePath());
    createEnemyItem(1,2,"element_0.png");
    
    data = new EnemyStatusData(0,    // enemyID,
                               "element_0.png",   //iconPath,
                               //std::string imagePath,
                               "EnemyName_0",     //enemyName,
                               ElementType::RED,  //type,
                               0,    //level,
                               10,   //hp,
                               1     //atk
                               );
    //createEnemyItem(1,2,data->getSpriteImagePath());
    createEnemyItem(2,0,"element_0.png");
    
    data = new EnemyStatusData(0,    // enemyID,
                               "element_0.png",   //iconPath,
                               //std::string imagePath,
                               "EnemyName_0",     //enemyName,
                               ElementType::RED,  //type,
                               0,    //level,
                               10,   //hp,
                               1     //atk
                               );
    //createEnemyItem(1,2,data->getSpriteImagePath());
    createEnemyItem(4,2,"element_0.png");
}



