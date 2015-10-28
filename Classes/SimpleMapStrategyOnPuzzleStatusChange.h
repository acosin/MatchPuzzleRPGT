//
//  SimpleMapStrategyOnPuzzleStatusChange.hpp
//  MatchPuzzleRPGT
//

#pragma once

#include "IMapStrategyOnPuzzleStatusChange.h"

class SimpleMapStrategyOnPuzzleStatusChange : public IMapStrategyOnPuzzleStatusChange
{
private:
    float durationEnemyDamageAnimation = 0.5;
public:
    void exec(MapController *c, PuzzleStatusChangeData *data) override;
};