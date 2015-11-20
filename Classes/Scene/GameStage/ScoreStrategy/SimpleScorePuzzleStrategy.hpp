//
//  SimpleScoreStrategy.hpp
//  MatchPuzzleRPGT
//

#pragma once

#include "IScorePuzzleStrategy.h"

class SimpleScorePuzzleStrategy : public IScorePuzzleStrategy
{
public:
    int getScoreToAdd(PuzzleStatusChangeData *data) override {
        CC_ASSERT(data != nullptr);
        
        int ret = 0;
        ret += (data->xCombo + data->yCombo) * data->getComboCount();
        
        return ret;
    }
};
