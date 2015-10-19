//
//  StageSelectScene.cpp
//  MatchPuzzleRPGT
//
//

#include "StageSelectScene.h"

StageSelectScene::StageSelectScene():
_layout(nullptr),
_background(nullptr),
_homeButton(nullptr),
_exitButton(nullptr),
_listView_selectStage(nullptr),
_stageManager(nullptr)
{
    
}

StageSelectScene::~StageSelectScene()
{
    
}


Scene* StageSelectScene::createScene()
{
	auto layer = StageSelectScene::create();
    
    auto scene = Scene::create();
	scene->addChild(layer);
	
    return scene;
}

bool StageSelectScene::init()
{
    if (Layer::init()==false) {
        return false;
    }
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    _stageManager = SceneMediator::getInstance()->getStageDataManager();
    _layout = CSLoader::createNode("ui/StageSelectScene.csb");
    _layout->setName("LAYOUT");
    
    // TODO: may create only once in SceneMediator?
    //_background = SceneMediator::getInstance()->getMainBackground();
    _background = MainBackground::create();
    _layout->getChildByName("ImageView_background")->addChild(_background);
    
    _homeButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_backHome"));
    _exitButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_exit"));
    
    _listView_selectStage = dynamic_cast<ui::ListView*>(_layout->getChildByName("ListView_selectStage"));
    fillListViewSelectStage();
    
    this->addChild(_layout);
    
    //initialize ui event listener
    _listView_selectStage->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(StageSelectScene::selectStage_callback, this));
    
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

bool StageSelectScene::fillListViewSelectStage()
{
    if (_stageManager == nullptr ||
        _listView_selectStage == nullptr) {
        return false;
    }
    
    // TODO: may need to handle exepction later
    
    for (auto recordIt : _stageManager->getStageScoreRecords()) {
        auto item = Item_SelectStage::createItem(recordIt.second);
        item->setAnchorPoint(Vec2(0.5,0.5));
        item->setPositionType(ui::Widget::PositionType::PERCENT);
        item->setPositionPercent(Vec2(0.5,0.5));
        item->setTouchEnabled(true);
        _listView_selectStage->pushBackCustomItem(item);
    }
    
    return true;
}

void StageSelectScene::selectStage_callback(Ref* pSender, ui::ListView::EventType type)
{
    if (type == ui::ListView::EventType::ON_SELECTED_ITEM_END) {
        auto listView = static_cast<ui::ListView*>(pSender);
        
        for (auto widget : listView->getItems()) {
            widget->getChildByName("Layer")->getChildByName<ui::Text*>("Text_stageName")->setColor(Color3B::WHITE);
        }
        
        auto selectedIndex = listView->getCurSelectedIndex();
        listView->getItem(selectedIndex)->getChildByName("Layer")->getChildByName<ui::Text*>("Text_stageName")->setColor(Color3B::GREEN);
        
        log("selected index %ld", selectedIndex);
        
        // TODO: select a stage and change scene here, may need more check about whether resources have been released
        SceneMediator::getInstance()->gotoGameStageScene(_stageManager, (uint32_t)selectedIndex);
    }
}