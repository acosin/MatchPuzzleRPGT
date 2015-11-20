//
//  SimpleScoreEnemyStrategy.h
//  MatchPuzzleRPGT
//


#pragma once

#include "IScoreEnemyStrategy.h"

class SimpleScoreEnemyStrategy : public IScoreEnemyStrategy
{
public:
    int getScoreToAdd(MapItemEnemy *enemy) override {
        CC_ASSERT(enemy != nullptr);
        
        int ret = 0;
        ret += enemy->getTotalHP() * enemy->getLevel();
        
        return ret;
    }
};
