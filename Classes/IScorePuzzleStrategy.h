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
    
public:
    virtual int getScoreToAdd(PuzzleStatusChangeData *data) = 0;
};