//
//  StageScoreRecord.h
//  MatchPuzzleRPGT
//

# pragma once

#include "StageData.h"
#include "TimeParser.hpp"

class StageScoreRecord
{
protected:
    StageData* _stageData;
    bool _scoreExist;
    int _bestScore;
    time_t _bestTimestamp;
    int _lastScore;
    time_t _lastTimestamp;
    
public:
    StageScoreRecord();
    ~StageScoreRecord();
    
    static StageScoreRecord* create(StageData* stageData);
    
    uint32_t getStageID();
    bool isScoreExist();
    int getBestScore();
    time_t getBestTimestamp();
    bool setBestScore(int score, time_t timestamp);
    bool setBestScore(int score);
    int getLastScore();
    time_t getLastTimestamp();
    void setLastScore(int score, time_t timestamp);
    void setLastScore(int score);
    bool updateScore(int score, time_t timestamp);
    bool updateScore(int score);
    
    const std::string getStageName();
    const std::string getStageIconPath();
    StageData* getStageData();
    
    static std::map<uint32_t, StageScoreRecord*> loadStageScoreRecordFromCSV(const std::string &filename, std::map<uint32_t, StageData*> &stageData);
    static bool writeStageScoreRecordsToCSV(const std::string &filename, std::map<uint32_t, StageScoreRecord*>& records);
};