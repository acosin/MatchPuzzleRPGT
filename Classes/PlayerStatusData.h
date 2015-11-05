//
//  PlayerStatusData.h
//  MatchPuzzleRPGT
//
//

#pragma once

struct PlayerStatusData {
    uint32_t playerID;
    
    // static data
    std::string playerIconPath;
    //std::string playerImagePath;
    
    // user data
    std::string playerName;
    
    // growth data
    int playerLevel;
    int exp;
    
    PlayerStatusData(uint32_t playerID,
                     std::string playerIconPath,
                     // user data
                     std::string playerName,
                     // growth data
                     int playerLevel,
                     int exp
                     )
    {
        init(playerID, playerIconPath, playerName, playerLevel, exp);
    }
    
    void init(uint32_t playerID,
              std::string playerIconPath,
              // user data
              std::string playerName,
              // growth data
              int playerLevel,
              int exp
              )
    {
        this->playerID = playerID;
        this->playerIconPath = playerIconPath;
        this->playerName = playerName;
        this->playerLevel = playerLevel;
        this->exp = exp;
    }
};


