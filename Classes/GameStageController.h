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

#include "PuzzleStatusChangeData.hpp"

#include "IClearStageCondition.h"
#include "StageClearData.h"

#include "StatusDataManager.h"

USING_NS_CC;

class MapController; //cross

class IClearStageCondition;
enum class ClearStageConditionType;

class StageClearData;

class GameStageController
{
public:
    static const std::string EventNameStageClear;
    static const std::string EventNameEnemyDead;
    static const std::string EventNameProcessGrowth;
private:
    StageData* _stageData;
    // map logic control
    MapController* _mapController;
    std::vector<IClearStageCondition*> _clearConditions;
    StageClearData * _clearData;
    
    StatusDataManager *_statusManager;
    
public:
    GameStageController();
    ~GameStageController();
    
    static GameStageController* create(StageData* stageData, StatusDataManager *statusManager);
    
    virtual bool initWithoutData();
    bool initWithData(StageData* stageData, StatusDataManager *statusManager);
    
    JewelsGrid* getJewelsGrid();
    
    MapLayer* getMapLayer();
    
    bool tryMovePlayerUp();
    bool tryMovePlayerDown();
    bool tryMovePlayerLeft();
    bool tryMovePlayerRight();
    
    void onPuzzleFinishComboes();
    
    void checkClearStage();
    void processClearStage(ClearStageConditionType t);
    int getPlayerX();
    int getPlayerY();
    StageData* getStageData();
    int getEnemyCount();
    PuzzleStatusChangeData* getPuzzleStatusChangeData();
    
    
    bool canAttackEnemy();
    
    void setScore(int score);
public:
    JewelsGrid* _jewelsGrid;

    
private:
    void addClearConditions();
};
