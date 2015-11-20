//
//  EnemyStatusData.h
//  MatchPuzzleRPGT
//

#pragma once

#include "ElementType.h"
#include "CsvParser.h"

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
    
    EnemyStatusData(uint32_t enemyID,
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
        init(enemyID,
             // static data
             iconPath,
             //imagePath,
             enemyName,
             type,
             level,
             hp,
             atk
             );
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
    
    //TODO: modify later
    std::string getSpriteImagePath() {
        return iconPath;
    }
    
    
    static std::map<uint32_t, EnemyStatusData*> loadEnemyDataFromCSV(const std::string &filename) {
        std::map<uint32_t, EnemyStatusData*> ret;
        
        // TODO: handle file open excpetion here
        auto fullFilename = FileUtils::getInstance()->fullPathForFilename(filename);
        CsvParser::Csv csv(fullFilename);
        
        // NOTE: i = 1 to discard header(csv[0])
        for (int i = 1; i < csv.getRowCount(); i++) {
            auto row = csv[i];
            uint32_t id = (uint32_t)(Value(row[0]).asInt());
            auto enemyDataTemp = new EnemyStatusData(id,         //uint32_t enemyID,
                                                     row[1],     //std::string iconPath,
                                                     row[2],     //std::string enemyName,
                                                     (ElementType)(Value(row[3]).asInt()), //ElementType type,
                                                     Value(row[4]).asInt(),              //int level,
                                                     Value(row[5]).asInt(),              //int hp,
                                                     Value(row[6]).asInt()              //int atk
                                                     );
            ret[id] = enemyDataTemp;
        }
        
        return ret;
    }
};
