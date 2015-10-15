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
    this->setCascadeOpacityEnabled(true);
}

StatusDataManager::~StatusDataManager()
{
    this->removeAllChildren();
}

StatusDataManager* StatusDataManager::create()
{
    auto m = new StatusDataManager();
    
    if (m && m->initWithoutData()) {
        m->autorelease();
        return m;
    }
    
    CC_SAFE_DELETE(m);
    
    return nullptr;
}

// TODO: may remove later
bool StatusDataManager::initWithoutData()
{
    if (Layer::init()==false)
        return false;
    
    return true;
}

// Note: playerData & unitRecords here should be managed by StatusDataManager
bool StatusDataManager::initWithData(PlayerStatusData* playerData, std::vector<UnitOfPlayerRecord*> &unitRecords)
{
    if (Layer::init()==false)
        return false;
    
    // TODO: init playerData, UnitRecords here, may check delete?
    _playerData = playerData;
    _unitRecords = unitRecords;
    
    return true;
}

// TODO: init for lacoal data
bool StatusDataManager::initFromLocalData()
{
    if (Layer::init()==false)
        return false;
    
    // TODO: init playerData, UnitRecords here from local data
    //
    
    loadUnitOfPlayerRecordsFromCSV("Data/UnitOfPlayerRecords.csv");
    
    return true;
}

void StatusDataManager::clearUnitRecords()
{
    for (auto record : _unitRecords) {
        delete record;
    }
    _unitRecords.clear();
}

bool StatusDataManager::loadUnitOfPlayerRecordsFromCSV(const std::string &fullpath)
{
    clearUnitRecords();
    UnitData unitDataTemp;
    UnitOfPlayerRecord* unitRecordTemp;
    
    CsvParser::Csv csv(FileUtils::getInstance()->fullPathForFilename(fullpath));
    // TODO: handle file open excpetion here
    
    for (int i = 0; i < csv.getRowCount(); i++) {
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
    
    
    return initWithData(playerData, unitRecords);
}