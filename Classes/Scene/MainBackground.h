//
//  MainBackground.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class MainBackground : public Node
{
protected:
    Sprite* _background;
    
public:
    MainBackground();
    virtual ~MainBackground();
    
    CREATE_FUNC(MainBackground);
    virtual bool init();
    virtual void update(float t);
};
