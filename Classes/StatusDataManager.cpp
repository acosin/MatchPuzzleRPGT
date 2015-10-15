//
//  StatusDataManager.cpp
//  MatchPuzzleRPGT
//
//

#include "StatusDataManager.h"
#include "time.h"


StatusDataManager::StatusDataManager():
_playerData(nullptr)
{
    
}

// NOTE: do not call release() here
StatusDataManager::~StatusDataManager()
{
    clearPlayerData();
    clearUnitRecords();
}

/**
 * StatusDataManagers created by this method have
 */
StatusDataManager* StatusDataManager::create()
{
    auto m = new StatusDataManager();
    
    if (m && m->initWithoutData()) {
        //m->autorelease();
        return m;
    }
    
    CC_SAFE_DELETE(m);
    
    return nullptr;
}

// TODO: may remove later
bool StatusDataManager::initWithoutData()
{
    return true;
}

// Note: playerData & unitRecords here should be managed by StatusDataManager
bool StatusDataManager::initWithData(PlayerStatusData* playerData, std::vector<UnitOfPlayerRecord*> &unitRecords)
{
    // TODO: init playerData, UnitRecords here, may check delete?
    _playerData = playerData;
    _unitRecords = unitRecords;
    
    return true;
}

// TODO: init for lacoal data
bool StatusDataManager::initFromLocalData(const std::string &playerDataFile, const std::string &unitRocordsFile)
{
    if (loadPlayerDataFromCSV(playerDataFile) == false)
        return false;
    
    if (loadUnitOfPlayerRecordsFromCSV(unitRocordsFile) == false)
        return false;
    
    return true;
}

void StatusDataManager::clearPlayerData()
{
    if (_playerData!= nullptr)
        delete _playerData;
}

void StatusDataManager::clearUnitRecords()
{
    for (auto record : _unitRecords) {
        delete record;
    }
    _unitRecords.clear();
}

bool StatusDataManager::loadPlayerDataFromCSV(const std::string &filename)
{
    clearPlayerData();
    
    // TODO: handle file open excpetion here
    CsvParser::Csv csv(FileUtils::getInstance()->fullPathForFilename(filename));
    
    auto row = csv[1];
    _playerData = new PlayerStatusData((uint32_t)(Value(row[0]).asInt()),
                                       row[1],
                                       row[2],
                                       Value(row[3]).asInt()
                                       );
    
    return true;
}

bool StatusDataManager::loadUnitOfPlayerRecordsFromCSV(const std::string &filename)
{
    clearUnitRecords();
    UnitData unitDataTemp;
    UnitOfPlayerRecord* unitRecordTemp;
    
    // TODO: handle file open excpetion here
    CsvParser::Csv csv(FileUtils::getInstance()->fullPathForFilename(filename));
    
    // NOTE: i = 1 to discard header(csv[0])
    for (int i = 1; i < csv.getRowCount(); i++) {
        auto row = csv[i];
        // TODO: may modify for any cols
        unitDataTemp.init((uint32_t)(Value(row[0]).asInt()),
                          row[1],
                          (ElementType)Value(row[2]).asInt(),
                          row[3],
                          Value(row[4]).asInt(),
                          Value(row[5]).asInt());
        // TODO: should load here later
        unitRecordTemp = new UnitOfPlayerRecord(unitDataTemp,
                                                time(nullptr));
        _unitRecords.push_back(unitRecordTemp);
    }
    
    return true;
}

PlayerStatusData* StatusDataManager::getPlayerStatusData()
{
    return _playerData;
}

std::vector<UnitOfPlayerRecord*> StatusDataManager::getUnitRecords()
{
    // TODO: should return a safe readable object instead
    return _unitRecords;
}

// TODO: for debug, remove later
bool StatusDataManager::initWithDebugData()
{
    PlayerStatusData* playerData = new PlayerStatusData(0,
                                                        "character_icon_0.png",
                                                        "Username_0",
                                                        100);
    
    std::vector<UnitOfPlayerRecord*> unitRecords;
    UnitData unitDataTemp;
    UnitOfPlayerRecord* unitRecordTemp;
    // unit 0
    unitDataTemp.init(0,
                      "element_red.png",
                      ElementType::RED,
                      "UnitName_0_red",
                      10,
                      1);
    unitRecordTemp = new UnitOfPlayerRecord(unitDataTemp,
                                            time(nullptr));
    unitRecords.push_back(unitRecordTemp);
    // unit 1
    unitDataTemp.init(1,
                      "element_blue.png",
                      ElementType::BLUE,
                      "UnitName_1_blue",
                      10,
                      1);
    unitRecordTemp = new UnitOfPlayerRecord(unitDataTemp,
                                            time(nullptr));
    unitRecords.push_back(unitRecordTemp);
    // unit 2
    unitDataTemp.init(2,
                      "element_yellow.png",
                      ElementType::YELLOW,
                      "UnitName_2_yellow",
                      10,
                      1);
    unitRecordTemp = new UnitOfPlayerRecord(unitDataTemp,
                                            time(nullptr));
    unitRecords.push_back(unitRecordTemp);
    // unit 3
    unitDataTemp.init(3,
                      "element_green.png",
                      ElementType::GREEN,
                      "UnitName_3_green",
                      10,
                      1);
    unitRecordTemp = new UnitOfPlayerRecord(unitDataTemp,
                                            time(nullptr));
    unitRecords.push_back(unitRecordTemp);
    // unit 4
    unitDataTemp.init(1,
                      "element_blue.png",
                      ElementType::BLUE,
                      "UnitName_1_blue",
                      10,
                      1);
    unitRecordTemp = new UnitOfPlayerRecord(unitDataTemp,
                                            time(nullptr));
    unitRecords.push_back(unitRecordTemp);
    // unit 5
    unitDataTemp.init(1,
                      "element_blue.png",
                      ElementType::BLUE,
                      "UnitName_1_blue",
                      10,
                      1);
    unitRecordTemp = new UnitOfPlayerRecord(unitDataTemp,
                                            time(nullptr));
    unitRecords.push_back(unitRecordTemp);
    
    return initWithData(playerData, _unitRecords);
}