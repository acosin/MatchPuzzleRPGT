//
//  ClearStageCondition_GoalMap.hpp
//  MatchPuzzleRPGT
//

#pragma once

#include "IClearStageCondition.h"

class ClearStageCondition_GoalMap : public IClearStageCondition
{
public:
    ClearStageCondition_GoalMap() {
        type = ClearStageConditionType::GOAL_MAP;
    };
    bool isClear(GameStageController *c) override;
};