//
//  UIHelper.h
//  MatchPuzzleRPGT
//

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class UIHelper
{
public:
    static void scaleToFixFather(Node* child, Node* father)
    {
        auto childSize = child->getContentSize();
        auto fatherSize = father->getContentSize();
        
        if (childSize.height == 0 && fatherSize.height == 0) {
            log("baga");
            return;
        }
        if (childSize.width/childSize.height < fatherSize.width/fatherSize.height) {
            child->setScale(fatherSize.height/childSize.height);
        } else {
            child->setScale(fatherSize.width/childSize.width);
        }
        child->setAnchorPoint(Vec2(0,0));
        child->setPosition(0,0);
        //anchorCenterToFather(child, father);
    }
    
    static void anchorCenterToFather(Node* child, Node* father)
    {
        auto fatherSize = father->getContentSize();
        child->setAnchorPoint(Vec2(0.5,0.5));
        child->setPosition(fatherSize.width/2, fatherSize.height/2);    }
};