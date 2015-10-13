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
    int level;
    
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
              int level)
    {
        init(unitID, unitIconPath, elementType, unitName, atk, level);
    }
    
    void init(uint32_t unitID,
              std::string unitIconPath,
              ElementType elementType,
              std::string unitName,
              // -- for battle system --
              int atk,
              int level
              )
    {
        this->unitID = unitID;
        this->unitIconPath = unitIconPath;
        this->elementType = elementType;
        this->unitName = unitName;
        this->atk = atk;
        this->level = level;
    }
    
    // TODO: note that not to add virtual function in a struct
    bool operator==(const UnitData& a) const
    {
        return (unitID== a.unitID);
    }
};

#endif /* defined(__MatchPuzzleRPGT__UnitData__) */