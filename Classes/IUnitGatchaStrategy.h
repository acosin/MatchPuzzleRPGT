//
//  IUnitGatchaStrategy.h
//  MatchPuzzleRPGT
//

#pragma once

#include "StatusDataManager.h"

class UnitGatchaResult
{
    
};

class IUnitGatchaStrategy
{
public:
    virtual UnitGatchaResult* getUnitByGatcha(StatusDataManager *statusManager) = 0;
    virtual bool canBasicGatcha(StatusDataManager *statusManager) = 0;
    virtual int getCoinsAfterGatcha(StatusDataManager *statusManager) = 0;
};