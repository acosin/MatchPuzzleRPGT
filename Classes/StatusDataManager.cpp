//
//  StatusDataManager.cpp
//  MatchPuzzleRPGT
//
//

#include "StatusDataManager.h"
#include "time.h"

#include <algorithm>


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
    playerDataFilename = playerDataFile;
    
    if (loadUnitOfPlayerRecordsFromCSV(unitRocordsFile) == false)
        return false;
    unitRocordsFilename = unitRocordsFile;
    
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
                                       Value(row[3]).asInt(),
                                       Value(row[4]).asInt()
                                       );
    
    return true;
}

bool StatusDataManager::writePlayerDataToCSV()
{
    std::vector<std::vector<string>> rows;
    std::vector<string> row;
    
    row.push_back("playerID");
    row.push_back("playerIconPath");
    row.push_back("playarName");
    row.push_back("playerLevel");
    row.push_back("exp");
    rows.push_back(row);
    row.clear();
    
    row.push_back(StringUtils::toString(_playerData->playerID));
    row.push_back(_playerData->playerIconPath);
    row.push_back(_playerData->playerName);
    row.push_back(StringUtils::toString(_playerData->playerLevel));
    row.push_back(StringUtils::toString(_playerData->exp));
    rows.push_back(row);
    row.clear();
    
    CsvParser::Csv::Write(FileUtils::getInstance()->fullPathForFilename(playerDataFilename), rows);
    rows.clear();
    
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
        
        // TODO: may process in another function
        if (i <= (int)ElementType::count) {
            unitRecordTemp->isSortie = true;
        } else {
            unitRecordTemp->isSortie = false;
        }
        _unitRecords.push_back(unitRecordTemp);
    }
    
    return true;
}

bool StatusDataManager::writeUnitOfPlayerRecordsToCSV()
{
    std::vector<std::vector<string>> rows;
    std::vector<string> row;
    
    row.push_back("unitID");
    row.push_back("unitIconPath");
    row.push_back("elementType");
    row.push_back("unitName");
    row.push_back("atk");
    row.push_back("level");
    rows.push_back(row);
    row.clear();
    
    for (auto record : _unitRecords) {
        auto unitdata = record->unitdata;
        row.push_back(StringUtils::toString(unitdata.unitID));
        row.push_back(unitdata.unitIconPath);
        row.push_back(StringUtils::toString((int)unitdata.elementType));
        row.push_back(unitdata.unitName);
        row.push_back(StringUtils::toString(unitdata.atk));
        row.push_back(StringUtils::toString(unitdata.level));
        rows.push_back(row);
        row.clear();
    }
    
    CsvParser::Csv::Write(FileUtils::getInstance()->fullPathForFilename(unitRocordsFilename), rows);
    rows.clear();
    
    return true;
}

PlayerStatusData* StatusDataManager::getPlayerStatusData()
{
    return _playerData;
}

void StatusDataManager::setPlayerLevel(int level)
{
    _playerData->playerLevel = level;
}

void StatusDataManager::setPlayerExp(int exp)
{
    _playerData->exp = exp;
}

UnitOfPlayerRecord* StatusDataManager::getDefaultUnit(ElementType type)
{
    auto index = (int)type;
    
    return _unitRecords[index];
}

bool StatusDataManager::changeDefaultUnitOfType(int index)
{
    auto recordToChange = _unitRecords[index];
    auto type = recordToChange->unitdata.elementType;
    (*(_unitRecords.begin()+index))->isSortie = true;
    (*(_unitRecords.begin()+(int)type))->isSortie = false;
    iter_swap(_unitRecords.begin()+index, _unitRecords.begin()+(int)type);
    
    // TODO: persistence here
    writeUnitOfPlayerRecordsToCSV();
    
    return true;
}

std::vector<UnitOfPlayerRecord*> StatusDataManager::getUnitRecords()
{
    // TODO: should return a safe readable object instead
    return _unitRecords;
}

std::map<int, UnitOfPlayerRecord*> StatusDataManager::getUnitRecordsOfType(ElementType type)
{
    std::map<int, UnitOfPlayerRecord*> ret;
    
    // NOTE: use iterator for linear speed 
    for (auto it = _unitRecords.begin(); it != _unitRecords.end(); it++) {
        if ((*it)->unitdata.elementType == type) {
            auto index = it - _unitRecords.begin();
            ret[index] = *it;
        }
    }
    
    return ret;
}

// TODO: for debug, remove later
bool StatusDataManager::initWithDebugData()
{
    PlayerStatusData* playerData = new PlayerStatusData(0,
                                                        "character_icon_0.png",
                                                        "Username_0",
                                                        100,
                                                        1000);
    
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