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
    std::string playarName;
    
    // growth data
    int playerLevel;
    
    PlayerStatusData(uint32_t playerID,
                     std::string playerIconPath,
                     // user data
                     std::string playarName,
                     // growth data
                     int playerLevel
                     )
    {
        init(playerID, playerIconPath, playarName, playerLevel);
    }
    
    void init(uint32_t playerID,
              std::string playerIconPath,
              // user data
              std::string playarName,
              // growth data
              int playerLevel
              )
    {
        this->playerID = playerID;
        this->playerIconPath = playerIconPath;
        this->playarName = playarName;
        this->playerLevel = playerLevel;
    }
};


