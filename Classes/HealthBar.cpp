//
//  HeathBar.cpp
//  MatchPuzzleRPGT
//

#include "HealthBar.h"

HealthBar::HealthBar() :
bgSprite(nullptr),
hpSprite(nullptr)
{
    
}

HealthBar::~HealthBar()
{
    
}

bool HealthBar::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    //TODO: may remove later
    if (!(Director::getInstance()->getTextureCache()->getTextureForKey(hpFile))) {
        Director::getInstance()->getTextureCache()->addImage(hpFile);
    }
    
    auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(hpFile);
    if (texture == nullptr) {
        return false;
    }
    hpSprite = Sprite::createWithTexture(texture);
    progressTimer = ProgressTimer::create(hpSprite);
    progressTimer->setType(ProgressTimer::Type::RADIAL);
    progressTimer->setReverseProgress(true);
    progressTimer->setPercentage(100.0);
    this->setContentSize(progressTimer->getContentSize());
    
    addChild(progressTimer);

    return true;
}

void HealthBar::setPercentage(float percentage)
{
    progressTimer->setPercentage(percentage);
    
}

float HealthBar::getPercentage()
{
    return progressTimer->getPercentage();
}

void HealthBar::animateFromTo(float duration, float fromPercentage, float toPercentage)
{
    progressTimer->runAction(ProgressFromTo::create(duration, fromPercentage, toPercentage));
}

void HealthBar::scaleSize(const cocos2d::Size &size)
{
    auto timerSize = progressTimer->getContentSize();
    progressTimer->setScale(size.width/timerSize.width, size.height/timerSize.height);
}
