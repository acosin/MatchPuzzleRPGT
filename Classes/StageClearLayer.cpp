//
//  StageClearScene.cpp
//  MatchPuzzleRPGT
//
//

#include "StageClearLayer.h"

#include "SimpleGrowthStrategyStageClear.hpp"

StageClearLayer::StageClearLayer()
{
    
}

StageClearLayer::~StageClearLayer()
{
    
}

bool StageClearLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    _layout = CSLoader::createNode("ui/StageClearLayer.csb");
    _layout->setName("LAYOUT");
    
    _clearInfo = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_clearInfo"));
    
    
    this->addChild(_layout);
    
    _growthStrategyStageClear = new SimpleGrowthStrategyStageClear();

    return true;
}

bool StageClearLayer::initWithData(StageClearData *data)
{
    CCLOG("StageClearLayer: handle StageClearData");
    return true;
}
