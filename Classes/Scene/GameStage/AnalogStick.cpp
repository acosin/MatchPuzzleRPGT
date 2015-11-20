//
//  AnalogStick.cpp
//  MatchPuzzleRPGT
//

#include "AnalogStick.h"

const double PI = 3.141592653;

AnalogStick::AnalogStick()
{
}

AnalogStick::~AnalogStick()
{
    
}

AnalogStick* AnalogStick::createStick(const std::string &stickImageName,
                                      const std::string &outerImageName,
                                      const Vec2 &pos)
{
    auto layer = AnalogStick::create();
    if (layer != nullptr) {
        layer->stickInit(stickImageName, outerImageName, pos);
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void AnalogStick::stickInit(const std::string &stickImageName,
                            const std::string &outerImageName,
                            const cocos2d::Vec2 &pos)
{
    auto outer = Sprite::create(outerImageName);
    outer->setPosition(pos);
    outer->setVisible(false);
    outer->setTag((int)TagForStickPart::tag_outer);
    addChild(outer);
    
    auto stick = Sprite::create(stickImageName);
    stick->setPosition(pos);
    stick->setVisible(false);
    stick->setTag((int)TagForStickPart::tag_stick);
    addChild(stick);
    
    stickOuterPosition = pos;
    stickOuterRadius = outer->getContentSize().width / 2;
    stickDirection = -1;
}

void AnalogStick::startStick()
{
    auto stick = (Sprite*)this->getChildByTag((int)TagForStickPart::tag_stick);
    stick->setVisible(true);
    auto outer = (Sprite*)this->getChildByTag((int)TagForStickPart::tag_outer);
    outer->setVisible(true);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan     = CC_CALLBACK_2(AnalogStick::onTouchBegan, this);
    touchListener->onTouchMoved     = CC_CALLBACK_2(AnalogStick::onTouchMoved, this);
    touchListener->onTouchEnded     = CC_CALLBACK_2(AnalogStick::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void AnalogStick::stopStick()
{
    auto stick = (Sprite*)this->getChildByTag((int)TagForStickPart::tag_stick);
    stick->setVisible(false);
    auto outer = (Sprite*)this->getChildByTag((int)TagForStickPart::tag_outer);
    outer->setVisible(false);
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeEventListenersForTarget(this);
}

float AnalogStick::getRad(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2)
{
    float px1 = pos1.x;
    float py1 = pos1.y;
    float px2 = pos2.x;
    float py2 = pos2.y;
    
    float x = px2 - px1;
    float y = py1 - py2;
    float c = sqrt(pow(x,2) + pow(y,2));
    float cosAngle = x / c;
    float rad = acos(cosAngle);
    //注意：当触屏的位置Y坐标<摇杆的Y坐标，去反值-0~-180
    if (py2 < py1)
    {
        rad = -rad;
    }
    return rad;
}

Vec2 getAnglePosition(float r, float angle) {
    return Vec2(r*cos(angle), r*sin(angle));
}

bool AnalogStick::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    auto pos = pTouch->getLocation();
    auto stick = (Sprite*)this->getChildByTag((int)TagForStickPart::tag_stick);
    if (stick->getBoundingBox().containsPoint(pos)) {
        isCanMove = true;
        return true;
    } else {
        return false;
    }
}

void AnalogStick::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    if (!isCanMove) {
        return;
    }
    
    auto pos = pTouch->getLocation();
    auto stick = (Sprite*)this->getChildByTag((int)TagForStickPart::tag_stick);
    float angle = getRad(stickOuterPosition, pos);
    if (sqrt(pow(stickOuterPosition.x-pos.x, 2)) + pow(stickOuterPosition.y-pos.y, 2) >=
        stickOuterRadius) {
        stick->setPosition(Vec2(stickOuterPosition.x, stickOuterPosition.y) + getAnglePosition(stickOuterRadius, angle));
    } else {
        stick->setPosition(pos);
    }
    
    if(angle>=-PI/4&&angle<PI/4)
    {
        stickDirection=(int)TagForDirection::right;
    }
    else if(angle>=PI/4&&angle<3*PI/4)
    {
        stickDirection=(int)TagForDirection::up;
    }
    else if((angle>=3*PI/4&&angle<=PI)||(angle>=-PI&&angle<-3*PI/4))
    {
        stickDirection=(int)TagForDirection::left;
    }
    else if(angle>=-3*PI/4&&angle<-PI/4)
    {
        stickDirection=(int)TagForDirection::down;
    }
}

void AnalogStick::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    if (!isCanMove) {
        return;
    }
    
    auto outer = (Sprite*)this->getChildByTag((int)TagForStickPart::tag_outer);
    auto stick = (Sprite*)this->getChildByTag((int)TagForStickPart::tag_stick);
    stick->stopAllActions();
    stick->runAction(MoveTo::create(0.8f, outer->getPosition()));
    isCanMove = false;
    stickDirection = (int)TagForDirection::stay;
}

