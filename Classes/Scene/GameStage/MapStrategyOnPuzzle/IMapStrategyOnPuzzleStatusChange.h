//
//  IMapStrategyOnPuzzleStatusChange.h
//  MatchPuzzleRPGT
//

#pragma once

#include "MapController.h"
#include "PuzzleStatusChangeData.hpp"

class MapController;

class IMapStrategyOnPuzzleStatusChange
{
public:
    virtual ~IMapStrategyOnPuzzleStatusChange() {}
    virtual void exec(MapController *c, PuzzleStatusChangeData *data) = 0;
};