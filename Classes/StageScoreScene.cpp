//
//  StageScoreScene.cpp
//  MatchPuzzleRPGT
//
//

#include "StageScoreScene.h"

StageScoreScene::StageScoreScene() :
_layout(nullptr),
_background(nullptr),
_homeButton(nullptr),
_exitButton(nullptr),
_listView_scoreRecords(nullptr),
_stageManager(nullptr)
{
    
}

StageScoreScene::~StageScoreScene()
{
    
}


Scene* StageScoreScene::createScene()
{
	auto layer = StageScoreScene::create();
    
    auto scene = Scene::create();
	scene->addChild(layer);
	
    return scene;
}

bool StageScoreScene::init()
{
    if (Layer::init()==false) {
        return false;
    }
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    _stageManager = SceneMediator::getInstance()->getStageDataManager();
    _layout = CSLoader::createNode("ui/StageScoreScene.csb");
    _layout->setName("LAYOUT");
    
    // TODO: may create only once in SceneMediator?
    //_background = SceneMediator::getInstance()->getMainBackground();
    _background = MainBackground::create();
    _layout->getChildByName("ImageView_background")->addChild(_background);
    
    _homeButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_backHome"));
    _exitButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_exit"));
    
    _listView_scoreRecords = dynamic_cast<ui::ListView*>(_layout->getChildByName("ListView_scoreRecords"));
    fillListViewScoreRecords();
    
    this->addChild(_layout);
    
    //initialize ui event listener
    
    // TODO: may used TouchListener
    _homeButton->addClickEventListener([](Ref* ref) {
        SceneMediator::getInstance()->gotoHomeScene();
    });
    
    _exitButton->addClickEventListener([](Ref* ref) {
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    });

    
    return true;
}

bool StageScoreScene::fillListViewScoreRecords()
{
    if (_stageManager == nullptr ||
        _listView_scoreRecords == nullptr) {
        return false;
    }
    
    // TODO: may need to handle exepction later
    
    for (auto record : _stageManager->getStageScoreRecords()) {
        auto item = Item_StageScoreRecord::createItem(record);
        item->setAnchorPoint(Vec2(0.5,0.5));
        item->setPositionType(ui::Widget::PositionType::PERCENT);
        item->setPositionPercent(Vec2(0.5,0.5));
        _listView_scoreRecords->pushBackCustomItem(item);
    }
    
    return true;
}
