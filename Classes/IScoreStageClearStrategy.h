//
//  IScoreStageClearStrategy.h
//  MatchPuzzleRPGT
//

#pragma once

#include "StageData.h"

class IScoreStageClearStrategy
{
public:
    virtual int getScoreToAdd(StageData *data) = 0;
};