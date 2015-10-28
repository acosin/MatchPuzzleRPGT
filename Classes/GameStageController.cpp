//
//  GameStageController.cpp
//  MatchPuzzleRPGT
//
//

#include "GameStageController.h"

#include "ClearStageCondition_GoalMap.h"

GameStageController::GameStageController():
_jewelsGrid(nullptr),
_stageData(nullptr)
{
    
}

GameStageController::~GameStageController()
{
    //TODO: may lead to some problem
    /*
    for (auto condition : _clearConditions) {
        CC_SAFE_DELETE(condition);
    }
    _clearConditions.clear();
     */
}

GameStageController* GameStageController::create(StageData *stageData)
{
    auto c = new GameStageController();
    
    if (c && c->initWithoutData()) {
        //m->autorelease();
        c->initWithData(stageData);
        return c;
    }
    
    CC_SAFE_DELETE(c);
    
    return nullptr;
}

bool GameStageController::initWithoutData()
{
    return true;
}

bool GameStageController::initWithData(StageData *stageData)
{
    _stageData = stageData;
    _mapController = new MapController(stageData);
    
    CC_ASSERT(_mapController->getMapLayer() != nullptr);
    
    //TODO: may grid size  here!_
    _jewelsGrid = JewelsGrid::create(6, 6);
    
    addClearConditions();
    
    return true;
}

JewelsGrid* GameStageController::getJewelsGrid()
{
    if (!_jewelsGrid) {
        _jewelsGrid = JewelsGrid::create(6, 6);
    }
    return _jewelsGrid;
}

MapLayer* GameStageController::getMapLayer()
{
    return _mapController->getMapLayer();
}


bool GameStageController::tryMovePlayerUp()
{
    bool ret;
    ret =  _mapController->tryMovePlayerUp();
    
    checkClearStage();
    return ret;
}

bool GameStageController::tryMovePlayerDown()
{
    bool ret;
    ret =  _mapController->tryMovePlayerDown();
    
    checkClearStage();
    return ret;
}

bool GameStageController::tryMovePlayerLeft()
{
    bool ret;
    ret =  _mapController->tryMovePlayerLeft();
    
    checkClearStage();
    return ret;
}

bool GameStageController::tryMovePlayerRight()
{
    bool ret;
    ret = _mapController->tryMovePlayerRight();
    
    checkClearStage();
    return ret;
}

void GameStageController::onPuzzleStatusChange()
{
    int damageX = _jewelsGrid->getStatusXCombo();
    int damageY = _jewelsGrid->getStatusYCombo();
    //TODO: show damage animation here
    auto changeData = new PuzzleStatusChangeData();
    changeData->xCombo = damageX;
    changeData->yCombo = damageY;
    
    //TODO: may need async here,
    //first stop stick controller to keep no playerItem change
    _mapController->onPuzzleStatusChange(changeData);
}

void GameStageController::checkClearStage()
{
    bool isClear = false;
    for (auto condition : _clearConditions) {
        if (condition->isClear(this)) {
            isClear = true;
            
            processClearStage(condition->type);
        }
    }
}

void GameStageController::processClearStage(ClearStageConditionType t)
{
    switch (t) {
        case ClearStageConditionType::GOAL_MAP:
            
            CCLOG("clear stage: goal map!");

            break;
            
        default:
            break;
    }
}


int GameStageController::getPlayerX()
{
    return _mapController->getPlayerX();
}

int GameStageController::getPlayerY()
{
    return _mapController->getPlayerY();
}

StageData* GameStageController::getStageData()
{
    return _stageData;
}

void GameStageController::addClearConditions()
{
    auto goalMap = new ClearStageCondition_GoalMap();
    _clearConditions.push_back(goalMap);
}

