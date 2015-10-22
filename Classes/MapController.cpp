//
//  MapController.cpp
//  MatchPuzzleRPGT
//
//

#include "MapController.h"

bool MapController::initMap(StageData *stageData)
{
    if (stageData == nullptr) {
        return false;
    }
    
    
    _stageData = stageData;
    //createEnemies();
    createEnemiesDebug();
    
    return true;
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
}


MapLayer* MapController::createMapLayerFromData()
{
    if (_stageData == nullptr ||
        _playerItem == nullptr) {
        return nullptr;
    }
    auto mapFilename = "map_00.tmx"; //TODO: get from _stageData
    auto playerFilename = "Player_on_map.png"; //TODO: get from _playerItem
    auto layer = MapLayer::create(mapFilename, playerFilename);
    return layer;
}

bool MapController::removeMapItem(uint32_t id)
{
    bool ret = false;
    
    if (_IDpool_mapItem->exist(id)) {
        auto it = findMapItem(id);
        _mapItems.erase(it);
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

// -- private --

//NOTE: not used

std::vector<IMapItem*>::iterator MapController::findMapItem(uint32_t id)
{
    std::vector<IMapItem*>::iterator it;
    for (it = _mapItems.begin(); it != _mapItems.end(); it++) {
        if ((*it)->getID() == id) {
            return it;
        }
    }
    return it;
}

std::vector<IMapItem*>::iterator MapController::findMapItem(IMapItem* ptr)
{
    return find(_mapItems.begin(), _mapItems.end(), ptr);
}

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
    //_enemyItems.push_back(new MapItemEnemy(1,2,data));
    
    data = new EnemyStatusData(0,    // enemyID,
                               "element_0.png",   //iconPath,
                               //std::string imagePath,
                               "EnemyName_0",     //enemyName,
                               ElementType::RED,  //type,
                               0,    //level,
                               10,   //hp,
                               1     //atk
                               );
    //_enemyItems.push_back(new MapItemEnemy(2,0,data));
    
    data = new EnemyStatusData(0,    // enemyID,
                               "element_0.png",   //iconPath,
                               //std::string imagePath,
                               "EnemyName_0",     //enemyName,
                               ElementType::RED,  //type,
                               0,    //level,
                               10,   //hp,
                               1     //atk
                               );
    //_enemyItems.push_back(new MapItemEnemy(4,2,data));
}



