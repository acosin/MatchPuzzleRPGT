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

};
