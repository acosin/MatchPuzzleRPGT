//
//  MainBackground.cpp
//  MatchPuzzleRPGT
//
//

#include "MainBackground.h"

MainBackground::MainBackground()
{
    // TODO: for debug, remove later
    log("MainBackground:create");
}

MainBackground::~MainBackground()
{
    this->unscheduleUpdate();
    // TODO: for debug, remove later
    log("MainBackground:unscheduleUpdate");
}

bool MainBackground::init()
{
    if (Node::init()==false) {
        return false;
    }
    
    _background = Sprite::create("mainBG.png");
    
    _background->setAnchorPoint(Vec2(0,0));
    
    Texture2D::TexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    _background->getTexture()->setTexParameters(tp);
    
    auto viewSize = Director::getInstance()->getVisibleSize();
    Rect rect(0, 0, viewSize.width, viewSize.height);
    
    _background->setTextureRect(rect);
    
    this->addChild(_background);
    this->scheduleUpdate();
    
    return true;
}

void MainBackground::update(float t)
{
    Node::update(t);
    
    auto rect = _background->getTextureRect();
    rect.origin.x += 100.0f*t;
    rect.origin.y += 100.0f*t;
    
    _background->setTextureRect(rect);
}