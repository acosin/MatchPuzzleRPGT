//
//  StageClearLayer.h
//  MatchPuzzleRPGT
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SceneMediator.h"
#include "StageClearData.h"

#include "IGrowthStrategyStageClear.h"

USING_NS_CC;

class StageClearLayer : public Layer
{
protected:
    Node* _layout;
    ui::Text *_clearInfo;
    IGrowthStrategyStageClear *_growthStrategyStageClear;
public:
    StageClearLayer();
    ~StageClearLayer();
    
    virtual bool init();
    CREATE_FUNC(StageClearLayer);
    
    bool initWithData(StageClearData *data);
private:

};
