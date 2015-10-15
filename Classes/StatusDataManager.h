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

/**
 * NOTE: StatusDataManager is a class need memory management manually! 
 */
class StatusDataManager 
{
protected:
    PlayerStatusData* _playerData;
    std::vector<UnitOfPlayerRecord*> _unitRecords;
    
    void clearPlayerData();
    void clearUnitRecords();
    
public:
    StatusDataManager();
    virtual ~StatusDataManager();
    
    static StatusDataManager* create();
    
    virtual bool initWithoutData(); // TODO: may remove later
    virtual bool initWithData(PlayerStatusData* playerData, std::vector<UnitOfPlayerRecord*> &unitRecords);
    virtual bool initFromLocalData(const std::string &playerDataFile, const std::string &unitRocordsFile);
    bool loadPlayerDataFromCSV(const std::string &filename);
    bool loadUnitOfPlayerRecordsFromCSV(const std::string& filename);
    
    std::vector<UnitOfPlayerRecord*> getUnitRecords();
    PlayerStatusData* getPlayerStatusData();
    
    // TODO: for debug, remove later
public:
    bool initWithDebugData();
};