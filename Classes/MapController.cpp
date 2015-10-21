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



