//
//  GameStageHUD.h
//  MatchPuzzleRPGT
//

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class GameStageHUD : public Layer
{
protected:
    
public:
    GameStageHUD();
    ~GameStageHUD();
    
    static cocos2d::Scene* createScene();
    virtual bool init();

    
    CREATE_FUNC(GameStageHUD);

private:

};

