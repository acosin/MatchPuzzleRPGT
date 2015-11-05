//
//  SimpleGrowthStrategyStageClear.hpp
//  MatchPuzzleRPGT
//

#pragma once

#include "IGrowthStrategyStageClear.h"

#include <map>

using namespace std;

class SimpleGrowthStrategyStageClear : public IGrowthStrategyStageClear
{
private:
    const int stageDifficultyFactor = 100;
    map<int,int> tableLevelExp;
    
public:
    SimpleGrowthStrategyStageClear() {
        loadTableLevelExp();
    }
    ~SimpleGrowthStrategyStageClear() {
        tableLevelExp.clear();
    }
    
    
    int getPlayerExp(StageClearData *data) override
    {
        int exp = 0;
        
        exp += data->score;
        exp += data->stageData->_difficulty * stageDifficultyFactor;
        
        return exp;
    }
    
    void unitGrowth(StageClearData *data) override
    {
        
    }
    
    void loadTableLevelExp() {
        int levelMax = 200;
        for (int lv = 0; lv <= levelMax; lv++) {
            tableLevelExp[lv] = 1000;
        }
    }
    
    int getNewLevel(int level, int &expCurrent, int expAdd) override {
        auto ret = level;
        CC_ASSERT(expAdd > 0);
        if (expCurrent + expAdd < tableLevelExp[ret]) {
            
        } else {
            expAdd = expCurrent + expAdd - tableLevelExp[ret];
            ret++;
            while (expAdd >= tableLevelExp[ret]) {
                expAdd -= tableLevelExp[ret];
                ret++;
            }
            expCurrent = expAdd;
        }
        
        return ret;
    }
    
};