//
//  Jewel.cpp
//  MatchPuzzleRPGT
//
//

#include "Jewel.h"


Jewel* Jewel::createByType(ElementType type, int x, int y)
{
    auto jewel = new Jewel();
    
    if (jewel && jewel->init(type, x, y))
    {
        jewel->autorelease();
        return jewel;
    }
    else
    {
        CC_SAFE_DELETE(jewel);
        return nullptr;
    }
}

bool Jewel::init(ElementType type, int x, int y)
{
    Sprite::init();
    
    _type = type;
    _x = x;
    _y = y;
    _isSwaping = false;
    _isCrushing = false;
    
    //NOTE: initialize textures by names, should be load some where first!
    auto name = ElementTypeUtils::getResourceFilename(_type);
    this->initWithFile(name);
    //this->initWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(name));
    
    this->setAnchorPoint(Vec2(0, 0)); //left bottom as anchor
    
    return true;
}

void Jewel::crush()
{
    //TODO: when crush, add the bonus (time) or other
    //GameStageScene::addBonus(1);
    
    //start crushing, set _isCrushing as true until the Action end,
    //and then remove the rendering node, set _isCrushing as false
    //开始消除，消除状态为真，直到消除动作结束，将宝石移除渲染节点，并置消除状态为假
    _isCrushing = true;
    auto action = FadeOut::create(0.2);
    auto call = CallFunc::create([this](){
        this->removeFromParent();
        _isCrushing = false;
    });
    this->runAction(Sequence::create(action, call, nullptr));
}