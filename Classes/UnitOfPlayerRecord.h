//
//  UnitOfPlayerRecord.h
//  MatchPuzzleRPGT
//
//

#ifndef UnitOfPlayerRecord_h
#define UnitOfPlayerRecord_h

#include "UnitData.h"

struct UnitOfPlayerRecord {
    UnitData unitdata;
    //unit32_t playerID;
    time_t getTimestamp;
};


#endif /* UnitOfPlayerRecord_h */
