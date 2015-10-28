//
//  IClearStageCondition.h
//  MatchPuzzleRPGT
//

#pragma once

#include "GameStageController.h"

class GameStageController;

enum class ClearStageConditionType {
    GOAL_MAP
};

class IClearStageCondition
{
public:
    ClearStageConditionType type;
public:
    virtual bool isClear(GameStageController *c) = 0;
};