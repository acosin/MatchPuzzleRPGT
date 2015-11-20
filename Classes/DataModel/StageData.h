//
//  StageData.h
//  MatchPuzzleRPGT
//
//

# pragma once

#include <map>
#include "CsvParser.h"

USING_NS_CC;

class StageData
{
public:
    uint32_t _stageID;
    std::string _stageName;
    uint32_t _mapID;
    std::string _mapName;
    std::string _stageIconPath;
    
    int _mapWidth;
    int _mapHeight;
    
    int _playerInitialX;
    int _playerInitialY;
    
    int _difficulty;
    
public:
    StageData(uint32_t stageID,
              std::string stageName,
              uint32_t mapID,
              std::string mapName,
              std::string stageIconPath,
              
              int mapWidth,
              int mapHeight,
              
              int playerInitialX,
              int playerInitialY,
        
              int difficulty);
    virtual ~StageData();
    
    inline bool operator==(const StageData& a) const
    {
        return (_stageID == a._stageID);
    }
    
    static std::map<uint32_t, StageData*> loadStageDataFromCSV(const std::string &filename);
    
    static std::string getMapTMXFilename(uint32_t mapID);
};