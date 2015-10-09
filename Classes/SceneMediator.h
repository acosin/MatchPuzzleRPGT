//
//  SceneMediator.h
//  MatchPuzzleRPGT
//
//

#ifndef __MatchPuzzleRPGT__SceneMediator__
#define __MatchPuzzleRPGT__SceneMediator__

#include "cocos2d.h"

#include "MainBackground.h"

USING_NS_CC;

class SceneMediator
{
protected:
    static SceneMediator* _instance;
    
    // TODO: may not maintain a common MainBackGround later
    static MainBackground* _mainBackground;
    
public:
    static SceneMediator* getInstance();
    
    // TODO: may not maintain a common MainBackGround later
    static MainBackground* getMainBackground();
    
    
    virtual void gotoHomeScene();
    virtual void gotoStageSelectScene();
    virtual void gotoGameStageScene();
    virtual void gotoStageScoreScene();
    virtual void gotoStatusScene();

private:

};

#endif /* defined(__MatchPuzzleRPGT__SceneMediator__) */