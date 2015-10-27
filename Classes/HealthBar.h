//
//  HeathBar.h
//  MatchPuzzleRPGT
//

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class HealthBar : public Node
{
protected:
    Sprite *bgSprite;
    Sprite *hpSprite;
    ProgressTimer *progressTimer;
    
    const std::string hpFile = "hp.png";
    
public:
    HealthBar();
    ~HealthBar();
    
    CREATE_FUNC(HealthBar);
    virtual bool init();
    
    void setPercentage(float percentage);
    float getPercentage();
    void animateFromTo(float duration, float fromPercentage, float toPercentage);
    void scaleSize(const Size& size);
};

