//
//  StageClearLayer.h
//  MatchPuzzleRPGT
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SceneMediator.h"
#include "StageClearData.h"

#include "IGrowthStrategyStageClear.h"
#include "IScoreStageClearStrategy.h"

USING_NS_CC;

class GrowthDataStageClear
{
public:
    int newPlayerLevel;
    int newPlayerExp;
    IGrowthStrategyStageClear *growthStrategy;
    StageClearData *clearData;
};

class StageClearLayer : public Layer
{
public:
    static int BonusKillAllEnemies;
protected:
    Node* _layout;
    ui::Text* _clearInfo;
    ui::Text* _textScore;
    ui::Text* _textScoreStage;
    ui::Text* _textScoreEnemy;
    ui::Text* _textScoreTotal;
    ui::Text* _textGrowthPlayer;
    ui::Text* _textGrowthPlayerResult;
    
    
    IGrowthStrategyStageClear *_growthStrategyStageClear;
    StageClearData *_clearData;
    IScoreStageClearStrategy *_scoreStageClearStrategy;
public:
    StageClearLayer();
    ~StageClearLayer();
    
    virtual bool init();
    CREATE_FUNC(StageClearLayer);
    
    bool initWithData(StageClearData *data);
private:
    void dispatchGrowthEvent(int newPlayerLevel, int newPlayerExp);
    void dispatchSaveScoreEvent(int score);
    void handleGrowthAndScore(int totalScore);
    void handleStageClear(int newPlayerLevel, int newPlayerExp, int score);
};
