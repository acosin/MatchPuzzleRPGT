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

std::map<uint32_t, StageData*> StageData::loadStageDataFromCSV(const std::string &filename)
{
    std::map<uint32_t, StageData*> ret;

    // TODO: handle file open excpetion here
    CsvParser::Csv csv(FileUtils::getInstance()->fullPathForFilename(filename));
    
    // NOTE: i = 1 to discard header(csv[0])
    for (int i = 1; i < csv.getRowCount(); i++) {
        auto row = csv[i];
        uint32_t id = (uint32_t)(Value(row[0]).asInt());
        auto stageDataTemp = new StageData(id,
                                           row[1],
                                           (uint32_t)(Value(row[2]).asInt()),
                                           row[3],
                                           row[4],
                                           Value(row[5]).asInt(),
                                           Value(row[6]).asInt(),
                                           Value(row[7]).asInt(),
                                           Value(row[8]).asInt(),
                                           Value(row[9]).asInt()
                                           );
        
        ret.insert(std::pair<uint32_t, StageData*>(id, stageDataTemp));
    }
    
    return ret;
}

std::string StageData::getMapTMXFilename(uint32_t mapID)
{
    char name[100] = {0};
    sprintf(name, "map_0%u.tmx", mapID);
    return std::string(name);
}
