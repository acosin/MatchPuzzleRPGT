//
//  PlayerAssetsData.cpp
//  MatchPuzzleRPGT
//
//

#include "PlayerAssetsData.h"

#include "cocos2d.h"

#include "CsvParser.h"

USING_NS_CC;

// -- public --

PlayerAssetsData::PlayerAssetsData() :
_coins(0)
{
    
}

PlayerAssetsData::~PlayerAssetsData()
{
    
}

int PlayerAssetsData::getCoins()
{
    return _coins;
}

bool PlayerAssetsData::loadPlayerAssetsFromCSV(std::string &filename)
{
    // TODO: handle file open excpetion here
    auto fullFilename = FileUtils::getInstance()->fullPathForFilename(filename);
    CsvParser::Csv csv(fullFilename);
    
    if (csv.getRowCount() == 0) {
        return false;
    }
    
    // NOTE: i = 1 to discard header(csv[0])
    for (int i = 1; i < csv.getRowCount(); i++) {
        
        auto row = csv[i];
        _coins = Value(row[0]).asInt();
    }
    
    return true;
}

// -- private --