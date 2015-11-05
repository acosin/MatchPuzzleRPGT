//
//  SimpleScoreStageClearStrategy.hpp
//  MatchPuzzleRPGT
//

#pragma once 

#include "IScoreStageClearStrategy.h"

class SimpleScoreStageClearStrategy : public IScoreStageClearStrategy
{
private:
    const int DifficultyFactor = 100;
public:
    int getScoreToAdd(StageData *data) {
        CC_ASSERT(data != nullptr);
        int ret = 0
        
        ret += data->_difficulty * DifficultyFactor;
        
        return ret;
    }
};