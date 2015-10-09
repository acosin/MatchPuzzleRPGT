//
//  HomeScene.h
//  MatchPuzzleRPGT
//
//

#ifndef __MatchPuzzleRPGT__HomeScene__
#define __MatchPuzzleRPGT__HomeScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class HomeScene : public cocos2d::Layer
{
protected:
    Node* _background;
    
    ui::Button* _startButton;
    ui::Button* _scoreButton;
    ui::Button* _statusButton;
    ui::Button* _exitButton;
    
public:
    HomeScene();
    ~HomeScene();
    
    CREATE_FUNC(HomeScene);
    virtual bool init();
    
    static Scene *createScene();
};

#endif /* defined(__MatchPuzzleRPGT__HomeScene__) */