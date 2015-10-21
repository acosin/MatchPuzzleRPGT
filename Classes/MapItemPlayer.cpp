//
//  MapItemPlayer.cpp
//  MatchPuzzleRPGT
//
//

#include "MapItemPlayer.h"


MapItemPlayer::MapItemPlayer(int x, int y)
{
    MapItemPlayer::MapItemPlayer(x,y,true);
}

MapItemPlayer::MapItemPlayer(int x, int y, bool movable)
{
    MapItemBase::MapItemBase(x,y,movable,MapItemType::Player);
}

MapItemPlayer::~MapItemPlayer()
{
    
}

void MapItemPlayer::setStatusData(PlayerStatusData *statusData)
{
    _statusData = statusData;
}