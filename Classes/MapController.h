//
//  MapController.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "StageData.h"
#include "MapItemEnemy.h"
#include "MapItemPlayer.h"
#include "MapLayer.h"

USING_NS_CC;

class MapController
{
private:
    StageData* _stageData;
    
    MapItemPlayer* _playerItem;
    int _lastPlayerX, _lastPlayerY;
    std::vector<MapItemEnemy*> _enemyItems;
    std::vector<IMapItem*> _mapItems;
public:
    
    bool initMap(StageData* stageData);
    
    int getPlayerX();
    int getPlayerY();
    void movePlayerTo(int x, int y);
    
    MapLayer* createMapLayerFromData();
private:
    void createEnemies();
    void createEnemiesDebug();
};
