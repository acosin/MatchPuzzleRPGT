//
//  GetUnitScene.hpp
//  MatchPuzzleRPGT
//

#pragma once


#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SceneMediator.h"

#include "IUnitGatchaStrategy.h"

#include "GatchaResultLayer.h"

USING_NS_CC;

class GetUnitScene : public Layer
{
private:
    float _duration_showConfirmGatcha = 0.5;
    float _duration_hideConfirmGatcha = 0.2;
protected:
    Node* _layout;
    Node* _background;
    GatchaResultLayer* _gatchaResultLayer;
    
    ui::Button* _homeButton;
    ui::Button* _exitButton;
    ui::Button* _unitGatchaButton;
    ui::Button* _debugCannotGatchaButton;
    ui::Button* _doGatchaButton;
    
    ui::ListView* _listView_unitRecords;;
    
    ui::Text* _text_coins;
    
    
    ui::Layout* _panel_maskGatchMsg;
    ui::Layout* _panel_confirmGatcha;
    ui::Text* _text_confirmGatcha;
    
    StatusDataManager* _statusManager;
    IUnitGatchaStrategy* _unitGatchaStrategy;
    
public:
    GetUnitScene();
    ~GetUnitScene();
    
    CREATE_FUNC(GetUnitScene);
    virtual bool init();
    
    static Scene *createScene();
    
private:
    bool fillListViewUnitRecords();
    void showPlayerAssets();
    void showConfirmGatcha();
    void handleCannotGatcha();
    void onClickMaskPanel();
    void handleCanGatcha();
    void onDoUnitGatcha();
    void executeUnitGatchaOnce();
    
    void regEventTapAfterAnimation();
    void removeEventTapAfterAnimation();
    void onEventTapAfterAnimation(EventCustom* pEvent);
};
