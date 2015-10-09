//
//  MainBackground.h
//  MatchPuzzleRPGT
//
//

#ifndef __MatchPuzzleRPGT__MainBackground__
#define __MatchPuzzleRPGT__MainBackground__

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

#endif /* defined(__MatchPuzzleRPGT__MainBackground__) */