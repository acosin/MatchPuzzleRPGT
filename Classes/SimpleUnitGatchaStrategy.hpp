//
//  SimpleUnitGatchaStrategy.hpp
//  MatchPuzzleRPGT
//

#pragma

#include "IUnitGatchaStrategy.h"

#define COINSBASICGATCHA 50

class SimpleUnitGatchaStrategy : public IUnitGatchaStrategy
{
private:
    int coinsBasicGatcha = 0;
public:
    SimpleUnitGatchaStrategy() {
        coinsBasicGatcha = COINSBASICGATCHA;
    }
    
    UnitGatchaResult* getUnitByGatcha(StatusDataManager *statusManager) override
    {
        UnitGatchaResult* ret;
        
        
        return ret;
    }
    
    bool canBasicGatcha(StatusDataManager *statusManager) override
    {
        if (statusManager->getPlayerCoins() < coinsBasicGatcha) {
            return false;
        } else {
            return true;
        }
    }
    
    int getCoinsAfterGatcha(StatusDataManager *statusManager) override
    {
        return (statusManager->getPlayerCoins() - coinsBasicGatcha);
    }
};