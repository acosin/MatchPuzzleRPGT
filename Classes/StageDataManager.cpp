//
//  StageDataManager.cpp
//  MatchPuzzleRPGT
//
//

#include "StageDataManager.h"

StageDataManager::StageDataManager()
{
    
}

StageDataManager::~StageDataManager()
{
    clearStageScoreRecords();
    clearStageData();
}

StageDataManager* StageDataManager::create()
{
    auto m = new StageDataManager();
    
    if (m && m->initWithoutData()) {
        //m->autorelease();
        return m;
    }
    
    CC_SAFE_DELETE(m);
    
    return nullptr;
}

void StageDataManager::clearStageScoreRecords()
{
    for (auto it = _stageScoreRecords.begin();it!=_stageScoreRecords.end();) {
        if (it->second != nullptr)
            delete it->second;
        _stageScoreRecords.erase(it);
    }}

void StageDataManager::clearStageData()
{
    for (auto it = _stageData.begin();it!=_stageData.end();) {
        if (it->second != nullptr)
            delete it->second;
        _stageData.erase(it);
    }
}

bool StageDataManager::initWithoutData()
{
    return true;
}

bool StageDataManager::initWithData(std::map<uint32_t, StageData*> stageData,
                                    std::map<uint32_t, StageScoreRecord*> stageScoreRecords)
{
    // TODO: may check delete?
    _stageData = stageData;
    _stageScoreRecords = stageScoreRecords;
    
    return true;
}

// TODO: need to handle exception here!
bool StageDataManager::initFromLocalData(const std::string &stageDataFile,
                                         const std::string &scoreRocordsFile)
{
    auto stageData = StageData::loadStageDataFromCSV(stageDataFile);
    auto scoreRecord = StageScoreRecord::loadStageScoreRecordFromCSV(scoreRocordsFile,
                                                                     stageData);
    
    return initWithData(stageData, scoreRecord);
}

std::map<uint32_t, StageScoreRecord*> StageDataManager::getStageScoreRecords()
{
    return _stageScoreRecords;
}

bool StageDataManager::initWithDebugData()
{
    std::map<uint32_t, StageScoreRecord*> stageScoreRecords;
    std::map<uint32_t, StageData*> stageDataAll;
    
    StageData* stageDataTemp;
    StageScoreRecord* recordTemp;
    // stage 0
    stageDataTemp = new StageData(0,                 //stageID
                                  "stageName_0",     //stageName
                                  0,                 //mapID
                                  "mapName_0",       //mapName
                                  "stageIcon_0.png", //stageIconPath
                                  
                                  5,                 //mapWidth
                                  4,                 //mapHeight,
                                  
                                  2,                 //playerInitialX
                                  0,                 //playerInitialY
                                  1                  //difficulty
                                  );
    recordTemp = StageScoreRecord::create(stageDataTemp);
    recordTemp->updateScore(700);
    recordTemp->updateScore(1000);
    stageDataAll[stageDataTemp->_stageID] = stageDataTemp;
    stageScoreRecords[stageDataTemp->_stageID] = recordTemp;
    // stage 1
    stageDataTemp = new StageData(1,                 //stageID
                                  "stageName_1",     //stageName
                                  1,                 //mapID
                                  "mapName_1",       //mapName
                                  "stageIcon_0.png", //stageIconPath
                                  
                                  5,                 //mapWidth
                                  5,                 //mapHeight,
                                  
                                  2,                 //playerInitialX
                                  0,                 //playerInitialY
                                  1                  //difficulty
                                  );
    recordTemp = StageScoreRecord::create(stageDataTemp);
    recordTemp->updateScore(600);
    recordTemp->updateScore(900);
    stageDataAll[stageDataTemp->_stageID] = stageDataTemp;
    stageScoreRecords[stageDataTemp->_stageID] = recordTemp;
    // stage 2
    stageDataTemp = new StageData(2,                 //stageID
                                  "stageName_2",     //stageName
                                  2,                 //mapID
                                  "mapName_2",       //mapName
                                  "stageIcon_0.png", //stageIconPath
                                  
                                  5,                 //mapWidth
                                  4,                 //mapHeight,
                                  
                                  2,                 //playerInitialX
                                  0,                 //playerInitialY
                                  1                  //difficulty
                                  );
    recordTemp = StageScoreRecord::create(stageDataTemp);
    recordTemp->updateScore(700);
    recordTemp->updateScore(1000);
    stageDataAll[stageDataTemp->_stageID] = stageDataTemp;
    stageScoreRecords[stageDataTemp->_stageID] = recordTemp;
    // stage 3
    stageDataTemp = new StageData(3,                 //stageID
                                  "stageName_3",     //stageName
                                  3,                 //mapID
                                  "mapName_3",       //mapName
                                  "stageIcon_0.png", //stageIconPath
                                  
                                  5,                 //mapWidth
                                  5,                 //mapHeight,
                                  
                                  2,                 //playerInitialX
                                  0,                 //playerInitialY
                                  3                  //difficulty
                                  );
    recordTemp = StageScoreRecord::create(stageDataTemp);
    recordTemp->updateScore(100);
    recordTemp->updateScore(300);
    stageDataAll[stageDataTemp->_stageID] = stageDataTemp;
    stageScoreRecords[stageDataTemp->_stageID] = recordTemp;
    // stage 4
    stageDataTemp = new StageData(4,                 //stageID
                                  "stageName_4",     //stageName
                                  0,                 //mapID
                                  "mapName_0",       //mapName
                                  "stageIcon_0.png", //stageIconPath
                                  
                                  5,                 //mapWidth
                                  4,                 //mapHeight,
                                  
                                  2,                 //playerInitialX
                                  0,                 //playerInitialY
                                  2                  //difficulty
                                  );
    recordTemp = StageScoreRecord::create(stageDataTemp);
    recordTemp->updateScore(300);
    recordTemp->updateScore(400);
    stageDataAll[stageDataTemp->_stageID] = stageDataTemp;
    stageScoreRecords[stageDataTemp->_stageID] = recordTemp;
    // stage 5
    stageDataTemp = new StageData(5,                 //stageID
                                  "stageName_5",     //stageName
                                  0,                 //mapID
                                  "mapName_0",       //mapName
                                  "stageIcon_0.png", //stageIconPath
                                  
                                  5,                 //mapWidth
                                  4,                 //mapHeight,
                                  
                                  2,                 //playerInitialX
                                  0,                 //playerInitialY
                                  3                  //difficulty
                                  );
    recordTemp = StageScoreRecord::create(stageDataTemp);
    recordTemp->updateScore(100);
    recordTemp->updateScore(200);
    stageDataAll[stageDataTemp->_stageID] = stageDataTemp;
    stageScoreRecords[stageDataTemp->_stageID] = recordTemp;
    
    return initWithData(stageDataAll, stageScoreRecords);
}