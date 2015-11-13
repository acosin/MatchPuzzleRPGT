//
//  IUnitGatchaStrategy.h
//  MatchPuzzleRPGT
//

#pragma once

#include "UnitData.h"
#include "StatusDataManager.h"

class UnitGatchaResult
{
    
};

class IUnitGatchaStrategy
{
public:
    virtual UnitGatchaResult* getUnitByGatcha(std::map<uint32_t, UnitData*> &unitData,
                                              StatusDataManager *statusManager) = 0;
};