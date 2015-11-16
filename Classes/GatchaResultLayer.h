//
//  GatchaResultLayer.h
//  MatchPuzzleRPGT
//

#pragma once


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "UnitData.h"

USING_NS_CC;

class GatchaResultLayer : public Layer
{
public:
    static const std::string EventNameTapAfterAnimation;
protected:
    int num_blinks;
    float duration_blink;
private:
    UnitData* _unitData;
    
    Node* _layout;
    ui::ImageView* _image_unit;
    ui::Text* _text_msg;
    ui::Layout* _panel_maskTop;
public:
    GatchaResultLayer();
    ~GatchaResultLayer();
    
    virtual bool init();
    CREATE_FUNC(GatchaResultLayer);
    static GatchaResultLayer* createLayer(UnitData* data);
    
    void showAnimation(CallFunc *callback);
private:
    void initUnitData(UnitData* data);
    void onMaskTopClick();
    void dispatchEventTapAfterAnimation();
};
