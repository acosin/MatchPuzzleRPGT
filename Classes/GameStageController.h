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
#include "MapController.h"

#include "PuzzleStatusChangeData.h"

#include "IClearStageCondition.h"

USING_NS_CC;

class IClearStageCondition;
enum class ClearStageConditionType;

class GameStageController
{
public:
    static const std::string EventNameStageClear;
private:
    StageData* _stageData;
    // map logic control
    MapController* _mapController;
    std::vector<IClearStageCondition*> _clearConditions;
    
public:
    GameStageController();
    ~GameStageController();
    
    static GameStageController* create(StageData* stageData);
    
    virtual bool initWithoutData();
    bool initWithData(StageData* stageData);
    
    JewelsGrid* getJewelsGrid();
    
    MapLayer* getMapLayer();
    
    bool tryMovePlayerUp();
    bool tryMovePlayerDown();
    bool tryMovePlayerLeft();
    bool tryMovePlayerRight();
    
    void onPuzzleStatusChange();
    
    void checkClearStage();
    void processClearStage(ClearStageConditionType t);
    int getPlayerX();
    int getPlayerY();
    StageData* getStageData();
    int getEnemyCount();
public:
    JewelsGrid* _jewelsGrid;

    
private:
    void addClearConditions();
};
