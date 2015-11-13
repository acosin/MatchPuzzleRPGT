//
//  GetUnitScene.cpp
//  MatchPuzzleRPGT
//

#include "GetUnitScene.h"


#include "StageSelectScene.h"

#include "ListItem_UnitRecord.h"
#include "SimpleUnitGatchaStrategy.hpp"

GetUnitScene::GetUnitScene():
_layout(nullptr),
_background(nullptr),
_homeButton(nullptr),
_exitButton(nullptr),
_unitGatchaButton(nullptr),
_unitGatchaStrategy(nullptr)
{
    
}

GetUnitScene::~GetUnitScene()
{
    
}


Scene* GetUnitScene::createScene()
{
    auto layer = GetUnitScene::create();
    
    auto scene = Scene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GetUnitScene::init()
{
    if (Layer::init()==false) {
        return false;
    }
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    _layout = CSLoader::createNode("ui/GetUnitScene.csb");
    _layout->setName("LAYOUT");
    
    // TODO: may create only once in SceneMediator?
    //_background = SceneMediator::getInstance()->getMainBackground();
    _background = MainBackground::create();
    _layout->getChildByName("ImageView_background")->addChild(_background);
    
    _listView_unitRecords = dynamic_cast<ui::ListView*>(_layout->getChildByName("ListView_UnitRecords"));
    
    _homeButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_backHome"));
    _exitButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_exit"));
    _unitGatchaButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_unitGatcha"));
    
    _statusManager = SceneMediator::getInstance()->getStatusDataManager();
    fillListViewUnitRecords();
    
    _text_coins = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_coins"));
    showPlayerAssets();
    
    this->addChild(_layout);
    
    
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
    
    _unitGatchaButton->addClickEventListener([](Ref* ref) {
        //TODO
    });

    
    _unitGatchaStrategy = new SimpleUnitGatchaStrategy();
    
    
    return true;
}


// -- private --

bool GetUnitScene::fillListViewUnitRecords()
{
    _listView_unitRecords->removeAllItems();
    if (_statusManager == nullptr ||
        _listView_unitRecords == nullptr) {
        return false;
    }
    
    // TODO: may need to handle exepction later
    auto records = _statusManager->getUnitRecords();
    
    for (auto it = records.begin(); it != records.end(); it++) {
        auto record = *it;
        auto index = it - records.begin();
        auto item = ListItem_UnitRecord::createListItem(record);
        item->setAnchorPoint(Vec2(0.5,0.5));
        item->setPositionType(ui::Widget::PositionType::PERCENT);
        item->setPositionPercent(Vec2(0.5,0.5));
        item->index = index;
        _listView_unitRecords->pushBackCustomItem(item);
    }
    
    return true;
}

void GetUnitScene::showPlayerAssets()
{
    std::string str_coins = "Coins:\n";
    str_coins += StringUtils::toString(_statusManager->getPlayerCoins());
    _text_coins->setString(str_coins);
}

