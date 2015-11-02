//
//  GameStageController.cpp
//  MatchPuzzleRPGT
//
//

#include "GameStageController.h"

#include "ClearStageCondition_GoalMap.h"
#include "ClearStageCondition_NoEnemy.h"
#include "StageClearData.h"

const string GameStageController::EventNameStageClear = "event_StageClear";

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

void GameStageController::onPuzzleFinishComboes()
{
    auto changeData = getPuzzleStatusChangeData();
    
    //TODO: may need async here,
    //first stop stick controller to keep no playerItem change
    _mapController->onPuzzleStatusChange(changeData);
    
    //TODO: handle changeData memory here
    delete changeData;
    
    checkClearStage();
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
    StageClearData *data;
    switch (t) {
        case ClearStageConditionType::GOAL_MAP:
            
            CCLOG("clear stage: goal map!");
            //process StageClearData

            break;
        case ClearStageConditionType::NO_ENEMY:
            CCLOG("clear stage: no enemy!");
            //process StageClearData

            break;
        default:
            break;
    }
    if (data != nullptr) { // now data == NULL
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        dispatcher->dispatchCustomEvent(GameStageController::EventNameStageClear, data);
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

int GameStageController::getEnemyCount()
{
    return _mapController->getEnemyCount();
}

PuzzleStatusChangeData* GameStageController::getPuzzleStatusChangeData()
{
    auto changeData = _jewelsGrid->createPuzzleStatusChangeData();
    //TODO:remove later
    int damageX = _jewelsGrid->getStatusXCombo();
    int damageY = _jewelsGrid->getStatusYCombo();
    changeData->xCombo = damageX;
    changeData->yCombo = damageY;
    //
    return changeData;
}

// TODO: [optimization] can maintain a flag after every move to avoid computing
bool GameStageController::canAttackEnemy()
{
    auto x = _mapController->getPlayerX();
    auto y = _mapController->getPlayerY();
    auto enemies = _mapController->getEnemyAround(x, y);
    auto count = enemies.size();
    enemies.clear();
    if (count == 0) {
        return false;
    } else {
        return true;
    }
}

void GameStageController::addClearConditions()
{
    auto goalMap = new ClearStageCondition_GoalMap();
    _clearConditions.push_back(goalMap);
    
    auto noEnemy = new ClearStageCondition_NoEnemy();
    _clearConditions.push_back(noEnemy);
}

