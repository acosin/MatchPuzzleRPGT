//
//  MapItemPlayer.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "MapItemBase.h"
#include "PlayerStatusData.h"

USING_NS_CC;

class MapItemPlayer : public MapItemBase
{
private:
    PlayerStatusData* _statusData;
public:
    MapItemPlayer(int x, int y);
    MapItemPlayer(int x, int y, bool movable);
    ~MapItemPlayer();
    
    void setStatusData(PlayerStatusData* statusData);

};
