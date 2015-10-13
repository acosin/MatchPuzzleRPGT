//
//  StatusScene.h
//  MatchPuzzleRPGT
//
//

#ifndef __MatchPuzzleRPGT__StatusScene__
#define __MatchPuzzleRPGT__StatusScene__

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SceneMediator.h"
#include "ListItem_UnitRecord.h"

USING_NS_CC;

class StatusScene : public Layer
{
protected:
    Node* _layout;
    Node* _background;
    
    ui::Button* _homeButton;
    ui::Button* _exitButton;
    ui::ListView* _listView_unitRecords;
    
    StatusDataManager* _statusManager;
    
public:
    StatusScene();
    ~StatusScene();
    
    CREATE_FUNC(StatusScene);
    virtual bool init();
    
    static Scene *createScene();
    
private:
    virtual bool fillListViewUnitRecords();
};

#endif /* defined(__MatchPuzzleRPGT__StatusScene__) */