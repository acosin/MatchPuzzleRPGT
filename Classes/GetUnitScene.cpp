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
_gatchaResultLayer(nullptr),
_homeButton(nullptr),
_exitButton(nullptr),
_unitGatchaButton(nullptr),
_unitGatchaStrategy(nullptr)
{
    
}

GetUnitScene::~GetUnitScene()
{
    removeEventTapAfterAnimation();
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
    _debugCannotGatchaButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_debugCannotGatcha"));
    _statusManager = SceneMediator::getInstance()->getStatusDataManager();
    fillListViewUnitRecords();
    
    _text_coins = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_coins"));
    showPlayerAssets();
    
    _panel_maskGatchMsg = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_maskGatchaMsg"));
    _panel_maskGatchMsg->setTouchEnabled(false);
    _panel_confirmGatcha = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_confirmGatcha"));
    _text_confirmGatcha = dynamic_cast<ui::Text*>(_panel_confirmGatcha->getChildByName("Text_confirmGatcha"));
    //_panel_confirmGatcha->setVisible(false);
    _panel_confirmGatcha->setOpacity(0);
    _panel_confirmGatcha->setTouchEnabled(false);
    _doGatchaButton = dynamic_cast<ui::Button*>(_panel_confirmGatcha->getChildByName("Button_doGatcha"));
    _doGatchaButton->setVisible(false);
    _doGatchaButton->setTouchEnabled(false);
    
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
    
    _unitGatchaButton->addClickEventListener([&](Ref* ref) {
        this->_unitGatchaButton->setTouchEnabled(false);
        this->showConfirmGatcha();
    });
    
    // NOTE: only for debug
    _debugCannotGatchaButton->addClickEventListener([&](Ref* ref) {
        this->handleCannotGatcha();
    });

    
    _panel_maskGatchMsg->addClickEventListener([&](Ref* ref) {
        this->onClickMaskPanel();
    });
    
    _doGatchaButton->addClickEventListener([&](Ref* ref) {
        this->onDoUnitGatcha();
    });
    
    regEventTapAfterAnimation();

    
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

void GetUnitScene::showConfirmGatcha()
{
    CCLOG("confirm gatcha");
    if (_unitGatchaStrategy->canBasicGatcha(_statusManager) == false) {
    //if (true) { // NOTE: for debug!
        handleCannotGatcha();
        return;
    }
    
    // Can basic gatcha
    handleCanGatcha();
}

void GetUnitScene::handleCannotGatcha()
{
    _doGatchaButton->setVisible(false);
    _doGatchaButton->setTouchEnabled(false);
    auto coinsAfter = _unitGatchaStrategy->getCoinsAfterGatcha(_statusManager);
    std::string msg = "Coins not enough!\n Coins:";
    msg += StringUtils::toString(_statusManager->getPlayerCoins()) + "->";
    msg += StringUtils::toString(coinsAfter);
    
    _text_confirmGatcha->setString(msg);
    auto fadeto = FadeTo::create(_duration_showConfirmGatcha, 255);
    auto callback = CallFunc::create([&](){
        // handle tap event
        this->_panel_confirmGatcha->setTouchEnabled(true);
        this->_panel_maskGatchMsg->setTouchEnabled(true);
        this->_unitGatchaButton->setTouchEnabled(true);
    });
    _panel_confirmGatcha->runAction(Sequence::create(fadeto,callback, NULL));

}

void GetUnitScene::onClickMaskPanel()
{
    CCLOG("click mask panel");
    //hide confirmgatcha
    auto fadeto = FadeTo::create(_duration_hideConfirmGatcha, 0);
    auto callback = CallFunc::create([&](){
        // handle tap event
        this->_panel_confirmGatcha->setTouchEnabled(false);
        this->_panel_maskGatchMsg->setTouchEnabled(false);
    });
    _panel_confirmGatcha->runAction(Sequence::create(fadeto,callback, NULL));
}

void GetUnitScene::handleCanGatcha()
{
    CCLOG("handleCanGatcha");
    auto coinsAfter = _unitGatchaStrategy->getCoinsAfterGatcha(_statusManager);
    std::string msg = "Confirm Gatcha?\n Coins:";
    msg += StringUtils::toString(_statusManager->getPlayerCoins()) + "->";
    msg += StringUtils::toString(coinsAfter);
    
    _text_confirmGatcha->setString(msg);
    auto fadeto = FadeTo::create(_duration_showConfirmGatcha, 255);
    auto callback = CallFunc::create([&](){
        // handle tap event
        this->_panel_confirmGatcha->setTouchEnabled(true);
        this->_panel_maskGatchMsg->setTouchEnabled(true);
        this->_unitGatchaButton->setTouchEnabled(true);
        
        this->_doGatchaButton->setTouchEnabled(true);
        this->_doGatchaButton->setVisible(true);
    });
    _panel_confirmGatcha->runAction(Sequence::create(fadeto,callback, NULL));
}

void GetUnitScene::onDoUnitGatcha()
{
    CCLOG("doUnitGatcha");
    auto fadeto = FadeTo::create(_duration_hideConfirmGatcha, 0);
    auto callback = CallFunc::create([&](){
        this->_panel_confirmGatcha->setTouchEnabled(false);
        auto coinsAfter = this->_unitGatchaStrategy->getCoinsAfterGatcha(this->_statusManager);
        this->_statusManager->changePlayerCoins(coinsAfter);
        this->showPlayerAssets();
        this->executeUnitGatchaOnce();
    });
    _panel_confirmGatcha->runAction(Sequence::create(fadeto,callback, NULL));
}

void GetUnitScene::executeUnitGatchaOnce()
{
    CCLOG("executeUnitGatchaOnce");
    
    // TODO: may need to delete memory of "result" for memory management optimization
    auto result = _unitGatchaStrategy->getUnitByGatcha(_statusManager);
    auto unitdata = _statusManager->getUnitData(result->unitID);
    // TODO: may delete memory of _gatchaResultLayer manually first here
    if (_gatchaResultLayer != nullptr) {
        this->removeChild(_gatchaResultLayer);
    }
    _gatchaResultLayer = GatchaResultLayer::createLayer(unitdata);
    _gatchaResultLayer->setOpacity(0);
    _gatchaResultLayer->setTouchEnabled(false);
    this->addChild(_gatchaResultLayer);
    
    _panel_maskGatchMsg->setTouchEnabled(false);
    _gatchaResultLayer->showAnimation(CallFunc::create([&](){
    }));
}


void GetUnitScene::regEventTapAfterAnimation()
{
    auto listenner =EventListenerCustom::create(GatchaResultLayer::EventNameTapAfterAnimation,
                                                CC_CALLBACK_1(GetUnitScene::onEventTapAfterAnimation, this));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(listenner, 100);
}

void GetUnitScene::removeEventTapAfterAnimation()
{
    getEventDispatcher()->removeCustomEventListeners(GatchaResultLayer::EventNameTapAfterAnimation);
}

void GetUnitScene::onEventTapAfterAnimation(EventCustom* pEvent)
{
    auto unitdata = static_cast<UnitData*>(pEvent->getUserData());
    auto newUnitID = unitdata->unitID;
    
    CCLOG("GetUnitScene::onEventTapAfterAnimation");
    _gatchaResultLayer->setVisible(false);
    this->removeChild(_gatchaResultLayer);
    
    this->_statusManager->addNewUnit(newUnitID);
    
    this->fillListViewUnitRecords();
}

