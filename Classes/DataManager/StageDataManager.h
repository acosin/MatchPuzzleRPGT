//
//  StageDataManager.h
//  MatchPuzzleRPGT
//
//

# pragma once

#include <vector>
#include "cocos2d.h"

#include "StageScoreRecord.h"

USING_NS_CC;

class StageDataManager
{
protected:
    std::map<uint32_t, StageScoreRecord*> _stageScoreRecords;
    std::map<uint32_t, StageData*> _stageData;
    std::string _scoreRecordsFilename;
    
    void clearStageScoreRecords();
    void clearStageData();
    
public:
    StageDataManager();
    virtual ~StageDataManager();
    
    static StageDataManager* create();
    
    virtual bool initWithoutData(); // TODO: may remove later
    virtual bool initWithData(std::map<uint32_t, StageData*> stageData,
                              std::map<uint32_t, StageScoreRecord*> stageScoreRecords);
    virtual bool initFromLocalData(const std::string &stageDataFile,
                                   const std::string &scoreRecordsFile);
    
    std::map<uint32_t, StageScoreRecord*> getStageScoreRecords();
    
    StageScoreRecord* getStageScoreRecord(uint32_t stageID);
    
    bool tryUpdateScore(uint32_t stageID, int score);
    
    // TODO: for debug, remove later
public:
    bool initWithDebugData();
};