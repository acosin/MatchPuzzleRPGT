//
//  IGrowthStrategyStageClear.h
//  MatchPuzzleRPGT
//

#pragma once

#include "StageClearData.h"
#include "UnitOfPlayerRecord.h"

class IGrowthStrategyStageClear
{
public:
    virtual ~IGrowthStrategyStageClear() {};
    virtual int getPlayerExp(StageClearData *data) = 0;
    virtual int getNewPlayerLevel(int level, int &expCurrent, int expAdd) = 0;
    virtual int getUnitExp(UnitOfPlayerRecord* record,
                           StageClearData *data,
                           int totalDamage) = 0;
    virtual int getNewUnitLevel(UnitOfPlayerRecord* record,
                                int &expCurrent,
                                int expAdd) = 0;
};