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
    MapItemPlayer(int x, int y, const std::string &imagePath);
    MapItemPlayer(int x, int y, bool movable, const std::string &imagePath);
    ~MapItemPlayer();
    
    void setStatusData(PlayerStatusData* statusData);

};
