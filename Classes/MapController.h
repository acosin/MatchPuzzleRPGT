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

#include "IDPool.h"

USING_NS_CC;

class MapController
{
private:
    StageData* _stageData;
    MapLayer* _mapLayer;
    
    IDPool* _IDpool_mapItem;
    MapItemPlayer* _playerItem;
    int _lastPlayerX, _lastPlayerY;
    std::vector<MapItemEnemy*> _enemyItems;
    std::vector<IMapItem*> _mapItems;
public:
    MapController();
    ~MapController();
    
    bool initMap(StageData* stageData);
    
    int getPlayerX();
    int getPlayerY();
    void movePlayerTo(int x, int y);
    
    MapLayer* createMapLayerFromData();
    
    bool removeMapItem(uint32_t id);
    bool removeMapItem(IMapItem* pItem);
    
    bool createPlayerItem(int x, int y, const std::string &imagePath);
    
private:
    std::vector<IMapItem*>::iterator findMapItem(uint32_t id);
    std::vector<IMapItem*>::iterator findMapItem(IMapItem* ptr);
    
    void createEnemies();
    void createEnemiesDebug();
};
