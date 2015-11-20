//
//  ClearStageCondition_NoEnemy.h
//  MatchPuzzleRPGT
//

#pragma

#include "IClearStageCondition.h"

class ClearStageCondition_NoEnemy : public IClearStageCondition
{
public:
    ClearStageCondition_NoEnemy() {
        type = ClearStageConditionType::NO_ENEMY;
    };
    bool isClear(GameStageController *c) override;
};