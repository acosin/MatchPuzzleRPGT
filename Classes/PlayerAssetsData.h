//
//  PlayerAssetsData.hpp
//  MatchPuzzleRPGT
//

#pragma once

class PlayerAssetsData
{
private:
    int _coins;
public:
    PlayerAssetsData();
    ~PlayerAssetsData();
    
    int getCoins();
    bool loadPlayerAssetsFromCSV(std::string & filename);
    
private:
};