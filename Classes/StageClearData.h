//
//  StageClearData.hpp
//  MatchPuzzleRPGT
//

#pragma once

#include "StageData.h"
#include "IClearStageCondition.h"

class StageData;
enum class ClearStageConditionType;

class StageClearData
{
public:
    StageData* stageData;
    int score;
    ClearStageConditionType type;
    
public:
    StageClearData();
    ~StageClearData();
    
};
