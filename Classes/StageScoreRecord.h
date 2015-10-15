//
//  StageScoreRecord.h
//  MatchPuzzleRPGT
//

# pragma once

#include "StageData.h"
#include "time.h"

class StageScoreRecord
{
protected:
    StageData* _stageData;
    int _bestScore;
    int _lastScore;
    time_t _bestTimestamp;
    
public:
    StageScoreRecord();
    ~StageScoreRecord();
};