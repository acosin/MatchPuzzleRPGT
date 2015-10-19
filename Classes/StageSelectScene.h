//
//  StageSelectScene.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SceneMediator.h"
#include "Item_SelectStage.hpp"

USING_NS_CC;

class StageSelectScene : public Layer
{
protected:
    Node* _layout;
    Node* _background;
    
    ui::Button* _homeButton;
    ui::Button* _exitButton;
    
    ui::ListView* _listView_selectStage;
    
    StageDataManager* _stageManager;
    
public:
    StageSelectScene();
    ~StageSelectScene();
    
    CREATE_FUNC(StageSelectScene);
    virtual bool init();
    
    static Scene *createScene();
    
    virtual bool fillListViewSelectStage();
    
    void selectStage_callback(Ref* pSender, ui::ListView::EventType type);
};
