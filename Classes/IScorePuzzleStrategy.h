//
//  IScoreStrategy.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "PuzzleStatusChangeData.hpp"

class IScorePuzzleStrategy
{
protected:
    
public:
    virtual ~IScorePuzzleStrategy() {}
    virtual int getScoreToAdd(PuzzleStatusChangeData *data) = 0;
};