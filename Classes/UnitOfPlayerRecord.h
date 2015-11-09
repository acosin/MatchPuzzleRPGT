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
    
    bool isSortie = false;
    
    UnitOfPlayerRecord(UnitData unitdata,
                       time_t getTimestamp)
    {
        init(unitdata, getTimestamp);
    }
    // TODO: here deep copy the UnitData
    void init(UnitData unitdata,
              time_t getTimestamp)
    {
        this->unitdata = unitdata;
        this->getTimestamp = getTimestamp;
    }
};


#endif /* UnitOfPlayerRecord_h */
