//
//  StageData.cpp
//  MatchPuzzleRPGT
//
//

#include "StageData.h"

StageData::StageData(uint32_t stageID,
                     std::string stageName,
                     uint32_t mapID,
                     std::string mapName,
                     std::string stageIconPath,
                     
                     int mapWidth,
                     int mapHeight,
                     
                     int playerInitialX,
                     int playerInitialY,
                     
                     int difficulty)
{
    _stageID =  stageID;
    _stageName = stageName;
    _mapID = mapID;
    _mapName = mapName;
    _stageIconPath = stageIconPath;
    
    _mapWidth = mapWidth;
    _mapHeight = mapHeight;
    
    _playerInitialX = playerInitialX;
    _playerInitialY = playerInitialY;
    
    _difficulty = difficulty;
}

StageData::~StageData()
{
    
}
