//
//  EnemyStatusData.h
//  MatchPuzzleRPGT
//

#pragma once

#include "ElementType.h"

struct EnemyStatusData {
    uint32_t enemyID; //enemy type id
    
    // static data
    std::string iconPath;
    //std::string imagePath;
    std::string enemyName;
    ElementType type;
    int level;
    int hp;
    int atk;
    
    EnemyStatusData(uint32_t playerID,
                     std::string playerIconPath,
                     // user data
                     std::string playerName,
                     // growth data
                     int playerLevel
                     )
    {
        init(enemyID,
             // static data
             iconPath,
             //imagePath,
             enemyName,
             type,
             level,
             hp,
             atk);
    }
    
    void init(uint32_t enemyID,
              // static data
              std::string iconPath,
              //std::string imagePath,
              std::string enemyName,
              ElementType type,
              int level,
              int hp,
              int atk
              )
    {
        this->enemyID = enemyID;
        this->iconPath = iconPath;
        this->enemyName = enemyName;
        this->type = type;
        this->level = level;
        this->hp = hp;
        this->atk = atk;
    }
};
