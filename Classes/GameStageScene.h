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

#include "StageClearLayer.h"
#include "StageClearData.h"

#include "ScoreBoard.h"
#include "IScorePuzzleStrategy.h"
#include "IScoreEnemyStrategy.h"

USING_NS_CC;

#define DELAY_PLAYER_MOVE 0.2

#define ELEMENT_TYPE_MATCH_COUNT_DELAY 0.1
#define COMBOES_COUNT_DOWN_DURATION    0.3
#define ATTACK_ANIMATION_DURATION      0.7

class GameStageScene : public Layer
{
protected:
    Node* _layout;
    Node* _puzzleLayout;
    Node* _mapLayout;
    Node* _background;
    ui::Layout* _puzzleEffectLayout;
    
    AnalogStick* _stick;
    
    ui::Button* _homeButton;
    ui::Button* _exitButton;
    ui::Button* _selectStageButton;
    
    
    uint32_t _stageID;
    StageData* _currentStageData;
    StageScoreRecord* _currentStageScore;
    StageDataManager* _stageManager;
    StatusDataManager* _statusManager;
    GameStageController* _controller;
    
    MapLayer* _mapLayer;
    
    ScoreBoard* _scoreBoard;
    IScorePuzzleStrategy* _scorePuzzleStrategy;
    IScoreEnemyStrategy* _scoreEnemyStrategy;
    
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
    
    virtual void update(float delta);
    
    void regEventJewelGridStatusChange();
    void removeEventJewelGridStatusChange();
    void onJewelGridStatusChange(EventCustom* pEvent);
    void regEventFinishComboes();
    void removeEventFinishComboes();
    void onFinishComboes(EventCustom* pEvent);
    
    void tryMovePlayerUp(float delay);
    void tryMovePlayerDown(float delay);
    void tryMovePlayerLeft(float delay);
    void tryMovePlayerRight(float delay);
    
    void regEventStageClear();
    void removeEventStageCLear();
    void onStageClear(EventCustom* pEvent);
    
    void regEventProgressGrowth();
    void removeEventProgressGrowth();
    void onProgressGrowth(EventCustom* pEvent);
    
    void stopInteraction();
    void startInteraction();
    
    virtual void animateComboCountChange(PuzzleStatusChangeData *data, float duration, CallFunc *callback=NULL);
    virtual void animateComboesCountDown(float duration, CallFunc *callback=NULL);
    void animateAttackAnimation(float duration, CallFunc *callback=NULL);
    static std::string getTextLabelComboCount(bool isX, ElementType type);
    void hideElementXYCount();
    void showElementXYCount();
    void processScoreForPuzzle();
    void regEventEnemyDead();
    void removeEventEnemyDead();
    void onEnemyDead(EventCustom* pEvent);
    
    // processing function in update()
    void processController();
    
};
