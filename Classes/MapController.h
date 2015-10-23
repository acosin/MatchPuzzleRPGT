//
//  MapController.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"
#include <map>
#include <vector>

#include "StageData.h"
#include "MapItemEnemy.h"
#include "MapItemPlayer.h"
#include "MapLayer.h"

#include "IDPool.h"

USING_NS_CC;

class MapController
{
private:
    StageData* _stageData = nullptr;
    MapLayer* _mapLayer = nullptr;
    
    IDPool* _IDpool_mapItem = nullptr;
    MapItemPlayer* _playerItem = nullptr;
    int _lastPlayerX, _lastPlayerY;
    std::map<uint32_t, MapItemEnemy*> _enemyItems;
    std::map<uint32_t, MapItemEnemy*> _mapItems;
public:
    MapController(StageData *stageData);
    ~MapController();
    
    bool initMap(StageData* stageData);
    MapLayer* getMapLayer();
    
    MapLayer* createMapLayerFromData();
    
    int getPlayerX();
    int getPlayerY();
    void movePlayerTo(int x, int y);
    bool createPlayerItem(int x, int y, const std::string &imagePath);
    
    bool moveMapItemTo(uint32_t id, int x, int y);
    std::vector<uint32_t> findMapItem(int x, int y);
    bool removeMapItem(uint32_t id);
    bool removeMapItem(IMapItem* pItem);
    
    //NOTE: return 0 if cannot create
    uint32_t createEnemyItem(int x, int y, const std::string &imagePath);
    
private:
    /*
    std::vector<IMapItem*>::iterator findMapItem(uint32_t id);
    std::vector<IMapItem*>::iterator findMapItem(IMapItem* ptr);
    */
    void createEnemies();
    void createEnemiesDebug();
};
