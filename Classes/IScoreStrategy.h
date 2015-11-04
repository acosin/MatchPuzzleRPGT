//
//  IScoreStrategy.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "GameStageController.h"


class IScoreStrategy
{
protected:
public:
    
public:
    virtual int getScoreToAdd(PuzzleStatusChangeData *data) = 0;
};