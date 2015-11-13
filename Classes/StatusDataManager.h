//
//  StatusDataManager.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include <vector>
#include <map>
#include "cocos2d.h"

#include "UnitOfPlayerRecord.h"
#include "PlayerStatusData.h"
#include "CsvParser.h"
#include "PlayerAssetsData.h"

USING_NS_CC;

/**
 * NOTE: StatusDataManager is a class need memory management manually! 
 */
class StatusDataManager 
{
protected:
    PlayerStatusData* _playerData;
    std::map<uint32_t, UnitData*> _unitData;
    std::vector<UnitOfPlayerRecord*> _unitRecords;
    PlayerAssetsData* _playerAssets;
    
    std::string playerDataFilename;
    std::string unitDataFilename;
    std::string unitOfPlayerRecordsFilename;
    std::string playerAssetsFilename;
    
private:
    
    void clearPlayerData();
    void clearUnitData();
    void clearUnitRecords();    
public:
    StatusDataManager();
    virtual ~StatusDataManager();
    
    static StatusDataManager* create();
    
    virtual bool initWithoutData(); // TODO: may remove later
    virtual bool initWithData(PlayerStatusData* playerData, std::vector<UnitOfPlayerRecord*> &unitRecords);
    virtual bool initFromLocalData(const std::string &playerDataFile,
                                   const std::string &unitDataFile,
                                   const std::string &unitOfPlayerRecordsFile,
                                   const std::string &playerAssetsFile);
    bool loadPlayerDataFromCSV(const std::string &filename);
    bool writePlayerDataToCSV();
    bool loadUnitDataFromCSV(const std::string &filename);
    bool writeUnitDataToCSV();
    bool loadUnitOfPlayerRecordsFromCSV(const std::string& filename);
    bool writeUnitOfPlayerRecordsToCSV();
    bool changePlayerCoins(int coins);
    
    std::map<uint32_t, UnitData*> getUnitData();
    std::vector<UnitOfPlayerRecord*> getUnitRecords();
    std::map<int, UnitOfPlayerRecord*> getUnitRecordsOfType(ElementType type);
    PlayerStatusData* getPlayerStatusData();
    
    // for growth
    void setPlayerLevel(int level);
    void setPlayerExp(int exp);
    
    UnitOfPlayerRecord* getDefaultUnit(ElementType type);
    UnitOfPlayerRecord* getUnitByIndex(int index);
    bool changeDefaultUnitOfType(int index);
    std::map<ElementType,int> getDefaultUnitsIndex();
    
    int getPlayerCoins();
public:
    // TODO: for debug, remove later
    bool initWithDebugData();
};