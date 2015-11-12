//
//  StageSelectScene.cpp
//  MatchPuzzleRPGT
//
//

#include "StageSelectScene.h"

#include "ListItem_UnitRecord.h"

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
    
    _panel_mask = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_mask"));
    _panel_mask->setOpacity(0);
    _panel_mask->setTouchEnabled(false);
    _listView_units = dynamic_cast<ui::ListView*>(_panel_mask->getChildByName("ListView_units"));
    _listView_units->setTouchEnabled(false);
    _button_cancelUnits = dynamic_cast<ui::Button*>(_panel_mask->getChildByName("Button_cancelUnits"));
    _button_saveUnits = dynamic_cast<ui::Button*>(_panel_mask->getChildByName("Button_saveUnits"));
    _button_saveUnits->setVisible(false);
    _button_saveUnits->setTouchEnabled(false);
    
    _statusManager = SceneMediator::getInstance()->getStatusDataManager();
    _unitsSortie.clear();
    _unitsSortie = _statusManager->getDefaultUnitsIndex();
    fillSortieUnits();
    
    
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

bool StageSelectScene::fillSortieUnits()
{
    // TODO: maintain a static ListItems here later for better performance
    for (int type = 0 ; type < (int)ElementType::count; type++) {
        auto str = "Image_defaultUnitIcon_" + Value(type).asString();
        auto image = dynamic_cast<ui::ImageView*>(_layout->getChildByName(str));
        auto record = _statusManager->getUnitByIndex(_unitsSortie[(ElementType)type]);
        image->loadTexture(record->unitdata->unitIconPath);
        
        image->addClickEventListener([&, type](Ref* ref) {
            this->_listView_units->removeAllItems();
            float timeFadeIn = 0.5;
            // TODO: guarantee no memory leak here
            auto recordsMap = this->_statusManager->getUnitRecordsOfType((ElementType)type);
            for (auto pair : recordsMap) {
                auto index = pair.first;
                auto recordTemp = pair.second;
                auto item = ListItem_UnitRecord::createListItem(recordTemp);
                bool isSortieOfItsType = this->_unitsSortie[(ElementType)type] == index;
                item->setSelected(isSortieOfItsType);
                item->setAnchorPoint(Vec2(0,0));
                item->setPositionType(ui::Widget::PositionType::PERCENT);
                item->setPositionPercent(Vec2(0.5,0.5));
                item->setScale(this->_listView_units->getContentSize().width/item->getContentSize().width, 1);
                item->setTouchEnabled(true);
                item->index = index;
                this->_listView_units->pushBackCustomItem(item);
            }
            
            this->_panel_mask->runAction(FadeIn::create(timeFadeIn));
            this->_panel_mask->setTouchEnabled(true);
            this->_listView_units->setTouchEnabled(true);
            this->_listView_units->setVisible(true);
        });
        
    }
    
    
    _listView_units->addEventListener([&](Ref *ref, ui::ListView::EventType eventType){
        //CCLOG("touch select");
        if (eventType == ui::ListView::EventType::ON_SELECTED_ITEM_END) {
            auto listview = static_cast<ui::ListView*>(ref);
            if (listview->getItems().size() <= 1) {
                return;
            }
            for (auto item : listview->getItems()) {
                auto listitem = dynamic_cast<ListItem_UnitRecord*>(item);
                listitem->setSelected(false);
            }
            auto selectedIndex = listview->getCurSelectedIndex();
            dynamic_cast<ListItem_UnitRecord*>(listview->getItem(selectedIndex))->setSelected(true);
            this->_button_saveUnits->setTouchEnabled(true);
            this->_button_saveUnits->setVisible(true);
        }
    });
    
    
    _button_cancelUnits->addClickEventListener([&](Ref* ref) {
        float timeFadeout = 0.5;
        this->_panel_mask->runAction(FadeOut::create(timeFadeout));
        //this->_listView_selectDefault->runAction(FadeOut::create(timeFadeout));
        this->_listView_units->setVisible(false);
        this->_panel_mask->setTouchEnabled(false);
        this->_button_saveUnits->setTouchEnabled(false);
        this->_button_saveUnits->setVisible(false);
        
        
    });
    
    _button_saveUnits->addClickEventListener([&](Ref* ref) {
        this->changeSortieUnitOfType();
        
        float timeFadeout = 0.5;
        this->_panel_mask->runAction(FadeOut::create(timeFadeout));
        this->_listView_units->setVisible(false);
        this->_panel_mask->setTouchEnabled(false);
        this->_button_saveUnits->setTouchEnabled(false);
        this->_button_saveUnits->setVisible(false);
    });
    
    return true;
}

void StageSelectScene::changeSortieUnitOfType()
{
    auto selectIndex = this->_listView_units->getCurSelectedIndex();
    auto item = dynamic_cast<ListItem_UnitRecord*>(this->_listView_units->getItem(selectIndex));
    _unitsSortie[item->type] = item->index;
    
    fillSortieUnits();
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
        SceneMediator::getInstance()->gotoGameStageScene(_stageManager, (uint32_t)selectedIndex, _unitsSortie);
    }
}