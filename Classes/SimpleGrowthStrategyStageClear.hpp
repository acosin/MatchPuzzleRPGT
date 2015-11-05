//
//  SimpleGrowthStrategyStageClear.hpp
//  MatchPuzzleRPGT
//

#pragma once

#include "IGrowthStrategyStageClear.h"

class SimpleGrowthStrategyStageClear : public IGrowthStrategyStageClear
{
private:
    const int stageDifficultyFactor = 100;
public:
    int getPlayerExp(StageClearData *data)
    {
        int exp = 0;
        
        exp += data->score;
        exp += data->stageData->_difficulty * stageDifficultyFactor;
        
        return exp;
    }
    
    void unitGrowth(StageClearData *data)
    {
        
    }
    
};