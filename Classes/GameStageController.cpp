//
//  GameStageController.cpp
//  MatchPuzzleRPGT
//
//

#include "GameStageController.h"

GameStageController::GameStageController():
_jewelsGrid(nullptr),
_stageData(nullptr)
{
    
}

GameStageController::~GameStageController()
{
    
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
    
    //TODO: may grid size  here!
    _jewelsGrid = JewelsGrid::create(6, 6);
    
    return true;
}

JewelsGrid* GameStageController::getJewelsGrid()
{
    return _jewelsGrid;
}

MapLayer* GameStageController::getMapLayer()
{
    return _mapController->getMapLayer();
}

