//
//  ClearStageCondition_GoalMap.cpp
//  MatchPuzzleRPGT
//
//
//

#include "ClearStageCondition_GoalMap.h"

bool ClearStageCondition_GoalMap::isClear(GameStageController *c)
{
    bool isGoal = false;
    
    auto stageData = c->getStageData();
    auto playerX = c->getPlayerX();
    auto playerY = c->getPlayerY();
    
    //TODO: may check multiple goal point later
    if (stageData->_mapWidth/2 == playerX && playerY == 0) {
        isGoal = true;
    }
    
    return isGoal;
}
