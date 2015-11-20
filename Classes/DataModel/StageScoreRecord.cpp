//
//  StageScoreRecord.cpp
//  MatchPuzzleRPGT
//

#include "StageScoreRecord.h"

StageScoreRecord::StageScoreRecord():
_stageData(nullptr),
_scoreExist(false),
_bestScore(-1),
_lastScore(-1)
{
    
}

// NOTE: should not delete _stageData here!
StageScoreRecord::~StageScoreRecord()
{
    /*
    if (_stageData != nullptr) {
        delete _stageData;
    }
    */
}


StageScoreRecord* StageScoreRecord::create(StageData* stageData)
{
    if (stageData == nullptr)
        return nullptr;
    auto ret = new StageScoreRecord();
    ret->_stageData = stageData;
    
    return ret;
}


uint32_t StageScoreRecord::getStageID()
{
    if (_stageData == nullptr)
        return UINT32_MAX;
    else
        return _stageData->_stageID;
}

bool StageScoreRecord::isScoreExist()
{
    return _scoreExist;
}

int StageScoreRecord::getBestScore()
{
    if (_scoreExist)
        return _bestScore;
    else
        return 0;
}

time_t StageScoreRecord::getBestTimestamp()
{
    return _bestTimestamp;
}

/*
 * NOTE: use updateScore() instead
 */
bool StageScoreRecord::setBestScore(int score, time_t timestamp)
{
    // NOTE: should use <= here because
    if (score <= _bestScore)
        return false;
    _bestScore = score;
    _bestTimestamp = timestamp;
    // NOTE: should only update _scoreExist in setLastScore()
    //_scoreExist = true;
    return true;
}

/*
 * NOTE: use updateScore() instead
 */
bool StageScoreRecord::setBestScore(int score)
{
    time_t timestamp = time(NULL);
    return setBestScore(score, timestamp);
}

int StageScoreRecord::getLastScore()
{
    if (_scoreExist)
        return _lastScore;
    else
        return 0;
}

time_t StageScoreRecord::getLastTimestamp()
{
    return _lastTimestamp;
}

void StageScoreRecord::setLastScore(int score, time_t timestamp)
{
    _lastScore = score;
    _lastTimestamp = timestamp;
    _scoreExist = true;
}

void StageScoreRecord::setLastScore(int score)
{
    time_t timestamp = time(NULL);
    setLastScore(score, timestamp);
}

bool StageScoreRecord::updateScore(int score, time_t timestamp)
{
    setLastScore(score, timestamp);
    return setBestScore(score, timestamp);
}

bool StageScoreRecord::updateScore(int score)
{
    time_t timestamp = time(NULL);
    return updateScore(score, timestamp);
}

const std::string StageScoreRecord::getStageName()
{
    return _stageData->_stageName;
}

const std::string StageScoreRecord::getStageIconPath()
{
    return _stageData->_stageIconPath;
}

StageData* StageScoreRecord::getStageData()
{
    return _stageData;
}


// TODO: throw exception here for load some record without data with the same stageID in stageData!
std::map<uint32_t, StageScoreRecord*> StageScoreRecord::loadStageScoreRecordFromCSV(const std::string &filename, std::map<uint32_t, StageData*> &stageData)
{
    std::map<uint32_t, StageScoreRecord*> ret;
    
    // TODO: handle file open excpetion here
    CsvParser::Csv csv(FileUtils::getInstance()->fullPathForFilename(filename));
    
    StageData* stageDataTemp;
    StageScoreRecord* recordTemp;
    // NOTE: i = 1 to discard header(csv[0])
    for (int i = 1; i < csv.getRowCount(); i++) {
        auto row = csv[i];
        uint32_t id = (uint32_t)(Value(row[0]).asInt());
        if (stageData.count(id) == 0) {
            log("StageScoreRecord::loadStageScoreRecordFromCSV: no stageData for the stageID %u", id);
        } else {
            stageDataTemp = stageData[id];
            recordTemp = StageScoreRecord::create(stageDataTemp);
            
            bool scoreExist = Value(row[1]).asBool();
            if (scoreExist) {
                int score = Value(row[2]).asInt();
                struct tm timestamp = TimeParser::StringToTM(Value(row[3]).asString());
                recordTemp->setBestScore(score, mktime(&timestamp));
                score = Value(row[4]).asInt();
                timestamp = TimeParser::StringToTM(Value(row[5]).asString());
                recordTemp->setLastScore(score, mktime(&timestamp));
            }
        }
        ret.insert(std::pair<uint32_t, StageScoreRecord*>(id, recordTemp));
    }
    
    return ret;
    
}

bool StageScoreRecord::writeStageScoreRecordsToCSV(const std::string &filename, std::map<uint32_t, StageScoreRecord *> &records)
{
    std::vector<std::vector<string>> rows;
    std::vector<string> row;
    
    row.push_back("stageId");
    row.push_back("scoreExist");
    row.push_back("bestScore");
    row.push_back("bestTimestamp");
    row.push_back("lastScore");
    row.push_back("lastTimeStamp");
    rows.push_back(row);
    row.clear();
    
    for (auto pair : records) {
        auto record = pair.second;
        
        row.push_back("stageId");
        row.push_back("scoreExist");
        row.push_back("bestScore");
        row.push_back("bestTimestamp");
        row.push_back("lastScore");
        row.push_back("lastTimeStamp");
        
        row.push_back(StringUtils::toString(record->getStageID()));
        row.push_back(record->isScoreExist()?"TRUE":"FALSE");
        row.push_back(StringUtils::toString(record->getBestScore()));
        time_t besttime =record->getBestTimestamp();
        row.push_back(StringUtils::toString(TimeParser::TMToString(*localtime(&besttime))));
        row.push_back(StringUtils::toString(record->getLastScore()));
        time_t lasttime =record->getLastTimestamp();
        row.push_back(StringUtils::toString(TimeParser::TMToString(*localtime(&lasttime))));
        rows.push_back(row);
        row.clear();
    }
    
    CsvParser::Csv::Write(FileUtils::getInstance()->fullPathForFilename(filename), rows);
    rows.clear();
    
    return true;
}