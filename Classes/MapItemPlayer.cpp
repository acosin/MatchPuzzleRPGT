//
//  MapItemPlayer.cpp
//  MatchPuzzleRPGT
//
//

#include "MapItemPlayer.h"


MapItemPlayer::MapItemPlayer(int x, int y, const std::string &imagePath)
:MapItemPlayer(x,y,true, imagePath)
{
}

MapItemPlayer::MapItemPlayer(int x, int y, bool movable, const std::string &imagePath)
:MapItemBase(x,y,movable,MapItemType::Player, imagePath)
{
}

MapItemPlayer::~MapItemPlayer()
{
    
}

void MapItemPlayer::setStatusData(PlayerStatusData *statusData)
{
    _statusData = statusData;
}