//
//  EnemyNode.h
//  MatchPuzzleRPGT
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "HealthBar.h"

USING_NS_CC;

class EnemyNode : public __LayerRGBA
{
private:
    ui::Layout* _panel_icon;
    ui::Layout* _panel_hp;
    
protected:
    Sprite *mapEnemy;
    HealthBar *hpBar;

public:
    EnemyNode();
    virtual ~EnemyNode();
    
    CREATE_FUNC(EnemyNode);
    virtual bool init();
    static EnemyNode* createNode(const std::string &enemyImage);
    
    void setPercentage(float percentage);
    float getPercentage();
    void animateFromTo(float duration, float fromPercentage, float toPercentage);
};
