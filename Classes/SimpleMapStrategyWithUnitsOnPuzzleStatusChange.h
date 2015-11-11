//
//  SimpleMapStrategyWithUnitsOnPuzzleStatusChange.hpp
//  MatchPuzzleRPGT
//

#pragma once

#include <map>
#include "IMapStrategyOnPuzzleStatusChange.h"

class SimpleMapStrategyWithUnitsOnPuzzleStatusChange : public IMapStrategyOnPuzzleStatusChange
{
private:
    float durationEnemyDamageAnimation = 0.5;
    std::map<ElementType, int> unitElementDamage;
public:
    SimpleMapStrategyWithUnitsOnPuzzleStatusChange();
    ~SimpleMapStrategyWithUnitsOnPuzzleStatusChange();
    
    void exec(MapController *c, PuzzleStatusChangeData *data) override;
};