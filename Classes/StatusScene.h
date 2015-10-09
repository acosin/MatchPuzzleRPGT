//
//  StatusScene.h
//  MatchPuzzleRPGT
//
//

#ifndef __MatchPuzzleRPGT__StatusScene__
#define __MatchPuzzleRPGT__StatusScene__

#include "cocos2d.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

class StatusScene : public Layer
{
protected:
    Node* _background;
    
    ui::Button* _homeButton;
    ui::Button* _exitButton;
    
public:
    StatusScene();
    ~StatusScene();
    
    CREATE_FUNC(StatusScene);
    virtual bool init();
    
    static Scene *createScene();
};

#endif /* defined(__MatchPuzzleRPGT__StatusScene__) */