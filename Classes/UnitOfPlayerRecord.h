//
//  UnitOfPlayerRecord.h
//  MatchPuzzleRPGT
//
//

#ifndef UnitOfPlayerRecord_h
#define UnitOfPlayerRecord_h

#include "UnitData.h"

struct UnitOfPlayerRecord {
    UnitData *unitdata;
    //unit32_t playerID;
    time_t getTimestamp;
    int level;
    int exp;
    
    bool isSortie = false;
    
    UnitOfPlayerRecord(UnitData *unitdata,
                       time_t getTimestamp,
                       int level,
                       int exp)
    {
        init(unitdata,
             getTimestamp,
             level,
             exp);
    }
    // TODO: here deep copy the UnitData
    void init(UnitData *unitdata,
              time_t getTimestamp,
              int level,
              int exp)
    {
        this->unitdata = unitdata;
        this->getTimestamp = getTimestamp;
        this->level = level;
        this->exp = exp;
    }
};


#endif /* UnitOfPlayerRecord_h */
