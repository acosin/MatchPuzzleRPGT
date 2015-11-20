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
    void setCoins(int coins);
    bool loadPlayerAssetsFromCSV(std::string & filename);
    bool writeToCSV(std::string &filename);
    
private:
};