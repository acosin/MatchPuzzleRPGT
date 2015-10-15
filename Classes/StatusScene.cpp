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
    
    _statusManager = SceneMediator::getStatusDataManager();
    _layout = CSLoader::createNode("ui/StatusScene.csb");
    _layout->setName("LAYOUT");
    
    // TODO: may create only once in SceneMediator?
    _background = MainBackground::create();
    _layout->getChildByName("ImageView_background")->addChild(_background);
    
    _homeButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_backHome"));
    _exitButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_exit"));
    
    _listView_unitRecords = dynamic_cast<ui::ListView*>(_layout->getChildByName("ListView_UnitRecords"));
    // add unit records to the listview
    fillListViewUnitRecords();
    
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

bool StatusScene::fillListViewUnitRecords()
{
    if (_statusManager == nullptr ||
        _listView_unitRecords == nullptr) {
        return false;
    }
    
    // TODO: may need to handle exepction later
    
    for (auto record : _statusManager->getUnitRecords()) {
        auto item = ListItem_UnitRecord::createListItem(record);
        // NOTE: setSizePercent() not work
        //item->setSizePercent(Vec2(90.0f, 50.0f));
        _listView_unitRecords->pushBackCustomItem(item);
    }
    
    return true;
}

