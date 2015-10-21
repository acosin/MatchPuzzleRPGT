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
    // map control
    std::vector<IMapItem*> mapItems;
    
public:
    GameStageController();
    ~GameStageController();
    
    static GameStageController* create(StageData* stageData);
    
    virtual bool initWithoutData();
    bool initWithData(StageData* stageData);
    
    
    JewelsGrid* getJewelsGrid();
};
