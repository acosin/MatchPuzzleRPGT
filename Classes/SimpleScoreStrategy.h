//
//  SimpleScoreStrategy.hpp
//  MatchPuzzleRPGT
//

#pragma once

#include "IScoreStrategy.h"

class SimpleScoreStrategy : public IScoreStrategy
{
public:
    int getScoreToAdd(PuzzleStatusChangeData *data) override {
        CC_ASSERT(data != nullptr);
        
        int ret = 0;
        ret += (data->xCombo + data->yCombo) * data->getComboCount();
        
        return ret;
    }
};
