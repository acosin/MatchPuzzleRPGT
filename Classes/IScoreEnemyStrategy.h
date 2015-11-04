//
//  IScoreEnemyStrategy.h
//  MatchPuzzleRPGT

#pragma once

#include "MapItemEnemy.h"

class IScoreEnemyStrategy
{
protected:
public:
    
public:
    virtual int getScoreToAdd(MapItemEnemy *enemy) = 0;
};