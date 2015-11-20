//
//  UnitData.h
//  MatchPuzzleRPGT
//
//

#ifndef __MatchPuzzleRPGT__UnitData__
#define __MatchPuzzleRPGT__UnitData__

#include <stdio.h>
#include "ElementType.h"

struct UnitData {
    uint32_t unitID;
    std::string unitIconPath;
    //std::string unitImagePath;
    ElementType elementType;
    std::string unitName;
    
    // -- for battle system --
    int atk;
    int rank;
    
    // -- end for battle system --
    UnitData()
    {
        
    }
    UnitData(uint32_t unitID,
              std::string unitIconPath,
              ElementType elementType,
              std::string unitName,
              // -- for battle system --
              int atk,
              int rank)
    {
        init(unitID,
             unitIconPath,
             elementType,
             unitName,
             atk,
             rank);
    }
    
    void init(uint32_t unitID,
              std::string unitIconPath,
              ElementType elementType,
              std::string unitName,
              // -- for battle system --
              int atk,
              int rank
              )
    {
        this->unitID = unitID;
        this->unitIconPath = unitIconPath;
        this->elementType = elementType;
        this->unitName = unitName;
        this->atk = atk;
        this->rank = rank;
    }
    
    // TODO: note that not to add virtual function in a struct
    bool operator==(const UnitData& a) const
    {
        return (unitID== a.unitID);
    }
};

#endif /* defined(__MatchPuzzleRPGT__UnitData__) */