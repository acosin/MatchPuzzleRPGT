//
//  MapItemEnemy.cpp
//  MatchPuzzleRPGT
//
//

#include "MapItemEnemy.h"


MapItemEnemy::MapItemEnemy(int x, int y)
{
    MapItemEnemy::MapItemEnemy(x,y,false);
}

MapItemEnemy::MapItemEnemy(int x, int y, bool movable)
{
    MapItemBase::MapItemBase(x,y,movable,MapItemType::Enemy);
}

MapItemEnemy::MapItemEnemy()
{
    
}

void MapItemEnemy::setStatusData(EnemyStatusData *statusData)
{
    _statusData = statusData;
}