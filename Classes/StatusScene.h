//
//  StatusScene.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SceneMediator.h"
#include "ListItem_UnitRecord.h"
#include "Layer_PlayerStatus.hpp"

USING_NS_CC;

class StatusScene : public Layer
{
protected:
    Node* _layout;
    Node* _background;
    
    ui::Button* _homeButton;
    ui::Button* _exitButton;
    ui::Layout* _panel_playerStatus;
    ui::ListView* _listView_unitRecords;
    ui::Layout* _panel_mask;
    ui::ListView* _listView_selectDefault;
    ui::Button* _button_cancelSelectDefault;
    
    StatusDataManager* _statusManager;
    
public:
    StatusScene();
    ~StatusScene();
    
    CREATE_FUNC(StatusScene);
    virtual bool init();
    
    static Scene *createScene();
    
private:
    virtual bool fillPanelPlayerStatus();
    virtual bool fillListViewUnitRecords();
    virtual bool fillDefaultUnits();
};
