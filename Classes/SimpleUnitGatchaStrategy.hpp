//
//  SimpleUnitGatchaStrategy.hpp
//  MatchPuzzleRPGT
//

#pragma

#include "IUnitGatchaStrategy.h"

class SimpleUnitGatchaStrategy : public IUnitGatchaStrategy
{
public:
    UnitGatchaResult* getUnitByGatcha(std::map<uint32_t, UnitData*> &unitData,
                                              StatusDataManager *statusManager) override
    {
        UnitGatchaResult* ret;
        
        
        
        
        return ret;
    }
    
    int getCoinsAfterGatcha(std::map<uint32_t, UnitData*> &unitData,
                            StatusDataManager *statusManager)
    {
        int ret = 0;
        
        
        return ret;
    }
};