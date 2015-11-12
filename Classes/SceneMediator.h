//
//  SceneMediator.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "MainBackground.h"
#include "StatusDataManager.h"
#include "StageDataManager.h"
#include "StageScoreScene.h"
#include "StageSelectScene.h"
#include "GameStageScene.h"
#include "GetUnitScene.h"

USING_NS_CC;

class SceneMediator
{
protected:
    static SceneMediator* _instance;
    MainBackground* _mainBackground = nullptr;
    StatusDataManager* _statusDataManager = nullptr;
    StageDataManager* _stageDataManager = nullptr;
    
public:
    static SceneMediator* getInstance();
    
    // TODO: may not maintain a common MainBackGround later
    MainBackground* getMainBackground();
    StatusDataManager* getStatusDataManager();
    StageDataManager* getStageDataManager();
    
    virtual void gotoHomeScene();
    virtual void gotoStageSelectScene();
    virtual void gotoGameStageScene(StageDataManager* stageDataManager, uint32_t stageID,
                                    std::map<ElementType, int> &unitsSortie);
    virtual void gotoStageScoreScene();
    virtual void gotoStatusScene();
    virtual void gotoGetUnitScene();

private:

};