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
    //std::string unitIconPath;
    //std::string unitImagePath;
    ElementType elementType;
    
    // TODO: note that not to add virtual function in a struct
    bool operator==(const UnitData& a) const
    {
        return (unitID== a.unitID);
    }
};

#endif /* defined(__MatchPuzzleRPGT__UnitData__) */