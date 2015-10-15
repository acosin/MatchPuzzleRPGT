//
//  SceneMediator.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "MainBackground.h"
#include "StatusDataManager.h"

USING_NS_CC;

class SceneMediator
{
protected:
    static SceneMediator* _instance;
    MainBackground* _mainBackground = nullptr;
    StatusDataManager* _statusDataManager = nullptr;
    
public:
    static SceneMediator* getInstance();
    
    // TODO: may not maintain a common MainBackGround later
    MainBackground* getMainBackground();
    StatusDataManager* getStatusDataManager();
    
    virtual void gotoHomeScene();
    virtual void gotoStageSelectScene();
    virtual void gotoGameStageScene();
    virtual void gotoStageScoreScene();
    virtual void gotoStatusScene();

private:

};