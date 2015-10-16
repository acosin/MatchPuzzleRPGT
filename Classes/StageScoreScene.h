//
//  StageScoreScene.h
//  MatchPuzzleRPGT
//
//

# pragma once

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SceneMediator.h"
#include "Item_StageScoreRecord.hpp"

USING_NS_CC;

class StageScoreScene : public Layer
{
protected:
    Node* _layout;
    Node* _background;
    
    ui::Button* _homeButton;
    ui::Button* _exitButton;
    
    ui::ListView* _listView_scoreRecords;
    
    StageDataManager* _stageManager;
    
public:
    StageScoreScene();
    ~StageScoreScene();
    
    CREATE_FUNC(StageScoreScene);
    virtual bool init();
    
    static Scene *createScene();
    
    
    virtual bool fillListViewScoreRecords();
};
