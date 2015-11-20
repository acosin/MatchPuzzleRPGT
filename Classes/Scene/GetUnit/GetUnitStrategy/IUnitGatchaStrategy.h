//
//  IUnitGatchaStrategy.h
//  MatchPuzzleRPGT
//

#pragma once

#include "StatusDataManager.h"

class UnitGatchaResult
{
public:
    uint32_t unitID;
};

class IUnitGatchaStrategy
{
public:
    virtual ~IUnitGatchaStrategy(){}
    virtual UnitGatchaResult* getUnitByGatcha(StatusDataManager *statusManager) = 0;
    virtual bool canBasicGatcha(StatusDataManager *statusManager) = 0;
    virtual int getCoinsAfterGatcha(StatusDataManager *statusManager) = 0;
};