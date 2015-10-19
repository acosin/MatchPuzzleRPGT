//
//  GameStageScene.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SceneMediator.h"
#include "GameStageController.h"

USING_NS_CC;

class GameStageScene : public Layer
{
protected:
    Node* _layout;
    Node* _puzzleLayout;
    Node* _background;
    
    ui::Button* _homeButton;
    ui::Button* _exitButton;
    ui::Button* _selectStageButton;
    
    uint32_t _stageID;
    StageData* _currentStageData;
    StageScoreRecord* _currentStageScore;
    StageDataManager* _stageManager;
    GameStageController* _controller;
    JewelsGrid* _jewelsGrid;
    
    bool initData(StageDataManager* stageManager, uint32_t stageID);
    
public:
    GameStageScene();
    ~GameStageScene();
    
    CREATE_FUNC(GameStageScene);
    virtual bool init();
    
    static Scene *createScene(StageDataManager* stageManager, uint32_t stageID);
};
