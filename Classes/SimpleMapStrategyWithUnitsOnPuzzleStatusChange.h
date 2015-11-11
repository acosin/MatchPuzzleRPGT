//
//  SimpleMapStrategyWithUnitsOnPuzzleStatusChange.hpp
//  MatchPuzzleRPGT
//

#pragma once


#include "IMapStrategyOnPuzzleStatusChange.h"

class SimpleMapStrategyWithUnitsOnPuzzleStatusChange : public IMapStrategyOnPuzzleStatusChange
{
private:
    float durationEnemyDamageAnimation = 0.5;
public:
    void exec(MapController *c, PuzzleStatusChangeData *data) override;
};