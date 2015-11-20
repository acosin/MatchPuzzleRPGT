//
//  GatchaResultLayer.cpp
//  MatchPuzzleRPGT
//

#include "GatchaResultLayer.h"

#define NUM_BLINKS 5
#define DURATION_BLINK 0.7

const std::string GatchaResultLayer::EventNameTapAfterAnimation = "EventNameTapAfterAnimation";

GatchaResultLayer::GatchaResultLayer() :
_unitData(nullptr)
{
    
}

GatchaResultLayer::~GatchaResultLayer()
{
    
}

bool GatchaResultLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    num_blinks = NUM_BLINKS;
    duration_blink = DURATION_BLINK;
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    _layout = CSLoader::createNode("ui/GatchaResultLayer.csb");
    _layout->setName("LAYOUT");
    
    _image_unit = dynamic_cast<ui::ImageView*>(_layout->getChildByName("Image_unitImage"));
    _text_msg = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_msg"));
    _text_msg->setVisible(false);
    _panel_maskTop = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_maskTop"));
    _panel_maskTop->setOpacity(0);
    _panel_maskTop->setTouchEnabled(false);
    
    this->addChild(_layout);
    
    
    _panel_maskTop->addClickEventListener([&](Ref* ref) {
        this->onMaskTopClick();
    });
    
    return true;
}

GatchaResultLayer* GatchaResultLayer::createLayer(UnitData* data)
{
    auto layer = GatchaResultLayer::create();
    
    layer->initUnitData(data);
    
    return layer;
}

void GatchaResultLayer::showAnimation(cocos2d::CallFunc *callback)
{
    this->_text_msg->setVisible(false);
    auto blink = Blink::create(duration_blink, num_blinks);
    auto showMsg = CallFunc::create([&](){
        this->_text_msg->setVisible(true);
        this->_panel_maskTop->setTouchEnabled(true);
    });
    _image_unit->runAction(Sequence::create(blink,
                                  showMsg,
                                  callback,
                                  NULL));
}


// -- private --

void GatchaResultLayer::initUnitData(UnitData *data)
{
    _unitData = data;
    
    _image_unit->loadTexture(data->unitIconPath);
    auto str_msg = data->unitName + "\n Get!";
    _text_msg->setString(str_msg);
}

void GatchaResultLayer::onMaskTopClick()
{
    _panel_maskTop->setTouchEnabled(false);
    
    dispatchEventTapAfterAnimation();
}

void GatchaResultLayer::dispatchEventTapAfterAnimation()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(GatchaResultLayer::EventNameTapAfterAnimation, _unitData);
}