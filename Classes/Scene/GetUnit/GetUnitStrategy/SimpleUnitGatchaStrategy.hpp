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
        UnitGatchaResult* ret = new UnitGatchaResult();
        
        auto unitdata = statusManager->getAllUnitData();
        auto it = unitdata.begin();
        std::random_device rd;
        std::mt19937 mt(rd());
        CC_ASSERT(unitdata.size() > 0);
        std::advance(it, mt() % unitdata.size());
        auto unitid = it->first;
        
        ret->unitID = unitid;
        
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