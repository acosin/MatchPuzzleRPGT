//
//  StatusDataManager.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "UnitOfPlayerRecord.h"
#include "PlayerStatusData.h"
#include "CsvParser.h"

USING_NS_CC;

class StatusDataManager : public Layer
{
protected:
    PlayerStatusData* _playerData;
    std::vector<UnitOfPlayerRecord*> _unitRecords;
    
    void clearUnitRecords();
    
public:
    StatusDataManager();
    virtual ~StatusDataManager();
    
    static StatusDataManager* create();
    
    virtual bool initWithoutData(); // TODO: may remove later
    virtual bool initWithData(PlayerStatusData* playerData, std::vector<UnitOfPlayerRecord*> &unitRecords);
    virtual bool initFromLocalData();
    bool loadUnitOfPlayerRecordsFromCSV(const std::string& fullpath);
    
    std::vector<UnitOfPlayerRecord*> getUnitRecords();
    
    // TODO: for debug, remove later
public:
    bool initWithDebugData();
};