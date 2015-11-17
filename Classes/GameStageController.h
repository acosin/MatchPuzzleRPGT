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
    static const std::string EventNameSaveScore;
private:
    StageData* _stageData;
    // map logic control
    MapController* _mapController;
    std::vector<IClearStageCondition*> _clearConditions;
    StageClearData * _clearData;
    
    StatusDataManager *_statusManager;
    std::map<ElementType, UnitOfPlayerRecord*> _unitsSortie;
    
public:
    GameStageController();
    ~GameStageController();
    
    static GameStageController* create(StageData* stageData, StatusDataManager *statusManager,
                                       std::map<ElementType, int> &unitsSortie);
    
    virtual bool initWithoutData();
    bool initWithData(StageData* stageData, StatusDataManager *statusManager,
                      std::map<ElementType, int> &unitsSortie);
    
    JewelsGrid* getJewelsGrid();
    
    MapLayer* getMapLayer();
    
    bool tryMovePlayerUp();
    bool tryMovePlayerDown();
    bool tryMovePlayerLeft();
    bool tryMovePlayerRight();
    bool tryMovePlayerTo(int x, int y);
    
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
    
    UnitOfPlayerRecord* getSortieUnitRecordByType(ElementType type);
    int getUnitDamage(ElementType type);
    void updateSortieUnitExp(ElementType type, int newExp);
    void updateSortieUnitLevel(ElementType type, int newLevel);
    
    // for path searching
    bool tryMovePlayerByAstar(const Point &target);
    void stopMapTouch();
    void startMapTouch();
    void animateMoveByPopAlongPath();
public:
    JewelsGrid* _jewelsGrid;

    
private:
    void addClearConditions();
};
