//
//  IScoreEnemyStrategy.h
//  MatchPuzzleRPGT

#pragma once

#include "MapItemEnemy.h"

class IScoreEnemyStrategy
{
    
public:
    virtual ~IScoreEnemyStrategy() {};
    virtual int getScoreToAdd(MapItemEnemy *enemy) = 0;
};