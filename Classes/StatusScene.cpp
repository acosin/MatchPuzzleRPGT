//
//  StatusScene.cpp
//  MatchPuzzleRPGT
//
//

#include "StatusScene.h"

#include "SceneMediator.h"

StatusScene::StatusScene():
_background(nullptr),
_homeButton(nullptr),
_exitButton(nullptr)
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
    
    // TODO: may create only once in SceneMediator?
    _background = MainBackground::create();
    this->addChild(_background);
    
    //initialize buttons
    _homeButton = ui::Button::create("home.png");
    _homeButton->setPosition(Vec2(viewSize.width/2, viewSize.height/2-340));
    addChild(_homeButton);
    
    _exitButton = ui::Button::create("exit.png");
    _exitButton->setPosition(Vec2(viewSize.width/2, viewSize.height/2-420));
    addChild(_exitButton);

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
