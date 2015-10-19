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
                                   const std::string &scoreRocordsFile);
    
    std::map<uint32_t, StageScoreRecord*> getStageScoreRecords();
    
    StageScoreRecord* getStageScoreRecord(uint32_t stageID);
    
    // TODO: for debug, remove later
public:
    bool initWithDebugData();
};