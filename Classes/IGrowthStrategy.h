//
//  IGrowthStrategy.h
//  MatchPuzzleRPGT
//

#pragma once

#include "GrowthData.hpp"

class IGrowthStrategy
{
public:
    void exec(GrowthData *data) = 0;
};