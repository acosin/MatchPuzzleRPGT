//
//  IScoreStageClearStrategy.h
//  MatchPuzzleRPGT
//

#pragma once

#include "StageData.h"

class IScoreStageClearStrategy
{
public:
    virtual ~IScoreStageClearStrategy() {}
    virtual int getScoreToAdd(StageData *data) = 0;
};