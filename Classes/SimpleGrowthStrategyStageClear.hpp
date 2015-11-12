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
    map<int,int> tableUnitLevelExp;
    
public:
    SimpleGrowthStrategyStageClear() {
        loadTableLevelExp();
        loadTableUnitLevelExp();
    }
    ~SimpleGrowthStrategyStageClear() {
        tableLevelExp.clear();
        tableUnitLevelExp.clear();
    }
    
    int getPlayerExp(StageClearData *data) override
    {
        int exp = 0;
        
        exp += data->score;
        exp += data->stageData->_difficulty * stageDifficultyFactor;
        
        return exp;
    }
    
    int getNewPlayerLevel(int level, int &expCurrent, int expAdd) override
    {
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
    
    int getUnitExp(UnitOfPlayerRecord* record,
                   StageClearData *data,
                   int totalDamage) override
    {
        //TODO: may use UnitOfPlayerRecord info later
        int exp = 0;
        exp += data->stageData->_difficulty * stageDifficultyFactor;
        exp += totalDamage;
        
        return exp;
    }
    
    void loadTableLevelExp() {
        int levelMax = 200;
        for (int lv = 0; lv <= levelMax; lv++) {
            tableLevelExp[lv] = 1000;
        }
    }
    
    void loadTableUnitLevelExp() {
        int levelMax = 200;
        for (int lv = 0; lv <= levelMax; lv++) {
            tableUnitLevelExp[lv] = 1000;
        }
    }
    
    int getNewUnitLevel(UnitOfPlayerRecord* record,
                        int &expCurrent,
                        int expAdd) override
    {
        auto ret = record->level;
        CC_ASSERT(expAdd > 0);
        if (record->exp + expAdd < tableUnitLevelExp[ret]) {
            
        } else {
            expAdd = record->exp + expAdd - tableUnitLevelExp[ret];
            ret++;
            while (expAdd >= tableUnitLevelExp[ret]) {
                expAdd -= tableUnitLevelExp[ret];
                ret++;
            }
        }
        expCurrent = expAdd;
        
        return ret;
    }

};