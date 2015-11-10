//
//  StatusDataManager.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include <vector>
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
    
    std::string playerDataFilename;
    std::string unitRocordsFilename;
private:
    
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
    bool writePlayerDataToCSV();
    bool loadUnitOfPlayerRecordsFromCSV(const std::string& filename);
    bool writeUnitOfPlayerRecordsToCSV();
    
    std::vector<UnitOfPlayerRecord*> getUnitRecords();
    std::map<int, UnitOfPlayerRecord*> getUnitRecordsOfType(ElementType type);
    PlayerStatusData* getPlayerStatusData();
    
    // for growth
    void setPlayerLevel(int level);
    void setPlayerExp(int exp);
    
    UnitOfPlayerRecord* getDefaultUnit(ElementType type);
    bool changeDefaultUnitOfType(int index);
public:
    // TODO: for debug, remove later
    bool initWithDebugData();
};