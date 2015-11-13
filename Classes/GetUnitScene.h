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

USING_NS_CC;

class GetUnitScene : public Layer
{
protected:
    Node* _layout;
    Node* _background;
    
    ui::Button* _homeButton;
    ui::Button* _exitButton;
    ui::Button* _unitGatchaButton;
    
    ui::ListView* _listView_unitRecords;;
    
    ui::Text* _text_coins;
    
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
    
};
