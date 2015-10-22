//
//  MapItemEnemy.cpp
//  MatchPuzzleRPGT
//
//

#include "MapItemEnemy.h"


MapItemEnemy::MapItemEnemy(int x, int y, const std::string &imagePath)
{
    MapItemEnemy::MapItemEnemy(x,y,false, imagePath);
}


MapItemEnemy::MapItemEnemy(int x, int y, bool movable, const std::string &imagePath)
{
    MapItemBase::MapItemBase(x,y,movable,MapItemType::Enemy,imagePath);
}

MapItemEnemy::MapItemEnemy(int x, int y, const std::string &imagePath, EnemyStatusData* statusData)
{
    MapItemEnemy::MapItemEnemy(x,y,imagePath);
    setStatusData(statusData);
}

MapItemEnemy::MapItemEnemy()
{
    
}

void MapItemEnemy::setStatusData(EnemyStatusData *statusData)
{
    _statusData = statusData;
}