//
//  StatusScene.cpp
//  MatchPuzzleRPGT
//
//

#include "StatusScene.h"

StatusScene::StatusScene():
_layout(nullptr),
_background(nullptr),
_homeButton(nullptr),
_exitButton(nullptr),
_panel_playerStatus(nullptr),
_listView_unitRecords(nullptr),
_statusManager(nullptr)
{
    
}

StatusScene::~StatusScene()
{
    
}

Scene* StatusScene::createScene()
{
	auto layer = StatusScene::create();
    
    auto scene = Scene::create();
	scene->addChild(layer);
	
    return scene;
}

bool StatusScene::init()
{
    if (Layer::init()==false) {
        return false;
    }
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    _statusManager = SceneMediator::getInstance()->getStatusDataManager();
    _layout = CSLoader::createNode("ui/StatusScene.csb");
    _layout->setName("LAYOUT");
    
    // TODO: may create only once in SceneMediator?
    //_background = SceneMediator::getInstance()->getMainBackground();
    _background = MainBackground::create();
    _layout->getChildByName("ImageView_background")->addChild(_background);
    
    _homeButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_backHome"));
    _exitButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_exit"));
    
    _panel_mask = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_mask"));
    _panel_mask->setOpacity(0);
    _panel_mask->setTouchEnabled(false);
    _listView_selectDefault = dynamic_cast<ui::ListView*>(_panel_mask->getChildByName("ListView_selectDefault"));
    _button_cancelSelectDefault = dynamic_cast<ui::Button*>(_panel_mask->getChildByName("Button_cancelSelectDefault"));
    
    _panel_playerStatus = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_PlayerStatus"));
    fillPanelPlayerStatus();
    _listView_unitRecords = dynamic_cast<ui::ListView*>(_layout->getChildByName("ListView_UnitRecords"));
    // add unit records to the listview
    fillListViewUnitRecords();
    fillDefaultUnits();
    
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

bool StatusScene::fillPanelPlayerStatus()
{
    if (_statusManager == nullptr ||
        _panel_playerStatus == nullptr) {
        return false;
    }
    
    auto playerData = _statusManager->getPlayerStatusData();
    auto item = Layer_PlayerStatus::createItem(playerData);
    // TODO: setPositionPercent() not works without calling setPositionType()
    item->setAnchorPoint(Vec2(0.5,0.5));
    item->setPositionType(ui::Widget::PositionType::PERCENT);
    item->setPositionPercent(Vec2(0.5,0.5));
    //item->setPosition(Vec2(0,100));
    _panel_playerStatus->addChild(item);
    
    return true;
}

bool StatusScene::fillListViewUnitRecords()
{
    if (_statusManager == nullptr ||
        _listView_unitRecords == nullptr) {
        return false;
    }
    
    // TODO: may need to handle exepction later
    
    for (auto record : _statusManager->getUnitRecords()) {
        auto item = ListItem_UnitRecord::createListItem(record);
        item->setAnchorPoint(Vec2(0.5,0.5));
        item->setPositionType(ui::Widget::PositionType::PERCENT);
        item->setPositionPercent(Vec2(0.5,0.5));
        _listView_unitRecords->pushBackCustomItem(item);
    }
    
    return true;
}

bool StatusScene::fillDefaultUnits()
{
    for (int type = 0; type < (int)ElementType::count; type++) {
        auto str = "Image_defaultUnitIcon_" + Value(type).asString();
        auto image = dynamic_cast<ui::ImageView*>(_layout->getChildByName(str));
        auto record = _statusManager->getDefaultUnit((ElementType)type);
        image->loadTexture(record->unitdata.unitIconPath);
        
        image->addClickEventListener([&, type](Ref* ref) {
            this->_listView_selectDefault->removeAllItems();
            float timeFadeIn = 0.8;
            CCLOG("tap");
            // TODO: guarantee no memory leak here
            auto recordsMap = this->_statusManager->getUnitRecordsOfType((ElementType)type);
            for (auto pair : recordsMap) {
                auto recordTemp = pair.second;
                auto item = ListItem_UnitRecord::createListItem(recordTemp);
                item->setAnchorPoint(Vec2(0,0));
                item->setPositionType(ui::Widget::PositionType::PERCENT);
                item->setPositionPercent(Vec2(0.5,0.5));
                item->setScale(this->_listView_selectDefault->getContentSize().width/item->getContentSize().width, 1);
                this->_listView_selectDefault->pushBackCustomItem(item);
            }
            
            this->_panel_mask->runAction(FadeIn::create(timeFadeIn));
            //this->_listView_selectDefault->runAction(FadeOut::create(timeFadeIn));
            this->_listView_selectDefault->setVisible(true);
            this->_panel_mask->setTouchEnabled(true);
        });

    }
    
    _button_cancelSelectDefault->addClickEventListener([&](Ref* ref) {
        float timeFadeout = 0.8;
        this->_panel_mask->runAction(FadeOut::create(timeFadeout));
        //this->_listView_selectDefault->runAction(FadeOut::create(timeFadeout));
        this->_listView_selectDefault->setVisible(false);
        this->_panel_mask->setTouchEnabled(false);
    });
    
    return true;
}

