//
//  MapItemEnemy.cpp
//  MatchPuzzleRPGT
//
//

#include "MapItemEnemy.h"


MapItemEnemy::MapItemEnemy(int x, int y, const std::string &imagePath)
:MapItemEnemy(x,y,false, imagePath)
{
}


MapItemEnemy::MapItemEnemy(int x, int y, bool movable, const std::string &imagePath)
:MapItemBase(x,y,movable,MapItemType::Enemy,imagePath)
{
}

MapItemEnemy::MapItemEnemy(int x, int y, const std::string &imagePath, EnemyStatusData* statusData)
:MapItemEnemy(x,y,imagePath)
{
    setStatusData(statusData);
}

MapItemEnemy::MapItemEnemy()
{
    
}

void MapItemEnemy::setStatusData(EnemyStatusData *statusData)
{
    CC_ASSERT(statusData != nullptr);
    _statusData = statusData;
    _currentHP = _statusData->hp;
}

int MapItemEnemy::getCurrentHP()
{
    return _currentHP;
}

int MapItemEnemy::getDamaged(int damange)
{
    CC_ASSERT(damange>=0);
    int res = _currentHP - damange;
    if (res <0) {
        res = 0;
    }
    _currentHP = res;
    return _currentHP;
}

bool MapItemEnemy::isDead()
{
    return (_currentHP == 0);
}