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
#include "MapLayer.h"
#include "UIHelper.hpp"
#include "AnalogStick.h"

USING_NS_CC;

class GameStageScene : public Layer
{
protected:
    Node* _layout;
    Node* _puzzleLayout;
    Node* _mapLayout;
    Node* _background;
    
    AnalogStick* _stick;
    
    ui::Button* _homeButton;
    ui::Button* _exitButton;
    ui::Button* _selectStageButton;
    
    
    uint32_t _stageID;
    StageData* _currentStageData;
    StageScoreRecord* _currentStageScore;
    StageDataManager* _stageManager;
    GameStageController* _controller;
    
    MapLayer* _mapLayer;
    
    bool initData(StageDataManager* stageManager, uint32_t stageID);
    
    int _texture_num = 0;
    void LoadTexture();
public:
    ui::Text* _textXcombo;
    ui::Text* _textYcombo;
    JewelsGrid* _jewelsGrid;
    
public:
    GameStageScene();
    ~GameStageScene();
    
    CREATE_FUNC(GameStageScene);
    virtual bool init();
    
    static Scene *createScene(StageDataManager* stageManager, uint32_t stageID);
private:
    void movePlayerTo(int x, int y);
    
    virtual void update(float delta);
    
    void regEventJewelGridStatusChange();
    void removeEventJewelGridStatusChange();
    void onJewelGridStatusChange(EventCustom* pEvent);

};
