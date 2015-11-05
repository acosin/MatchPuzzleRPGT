//
//  IGrowthStrategyStageClear.h
//  MatchPuzzleRPGT
//

#pragma once

#include "StageClearData.h"

class IGrowthStrategyStageClear
{
public:
    virtual int getPlayerExp(StageClearData *data) = 0;
    virtual void unitGrowth(StageClearData *data) = 0;
    virtual int getNewLevel(int level, int &expCurrent, int expAdd) = 0;
};