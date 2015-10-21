//
//  GameStageController.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"
#include "JewelGrid.h"
#include "StageData.h"
#include "StageScoreRecord.h"
#include "IMapItem.h"

USING_NS_CC;

class GameStageController
{
private:
    JewelsGrid* _jewelsGrid;
    StageData* _stageData;
    // map logic control
    std::vector<IMapItem*> _mapItems;
    IMapItem* _playerItem;
    
    int _lastPlayerX, _lastPlayerY;
    
public:
    GameStageController();
    ~GameStageController();
    
    static GameStageController* create(StageData* stageData);
    
    virtual bool initWithoutData();
    bool initWithData(StageData* stageData);
    
    Vec2 getPlayerPos();
    void movePlayerTo(int x, int y);
    
    JewelsGrid* getJewelsGrid();
};
