//
//  ClearStageCondition_NoEnemy.cpp
//  MatchPuzzleRPGT
//
//

#include "ClearStageCondition_NoEnemy.h"


bool ClearStageCondition_NoEnemy::isClear(GameStageController *c)
{
    if (c->getEnemyCount() > 0) {
        return false;
    } else {
        return true;
    }
}
