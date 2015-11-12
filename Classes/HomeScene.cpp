//
//  HomeScene.cpp
//  MatchPuzzleRPGT
//
//

#include "HomeScene.h"
#include "SceneMediator.h"

HomeScene::HomeScene():
_background(nullptr),
_startButton(nullptr),
_scoreButton(nullptr),
_statusButton(nullptr),
_getUnitButton(nullptr),
_exitButton(nullptr)
{
    
}

HomeScene::~HomeScene()
{
    
}


Scene* HomeScene::createScene()
{
	auto layer = HomeScene::create();
    
    auto scene = Scene::create();
	scene->addChild(layer);
	
    return scene;
}

bool HomeScene::init()
{
    if (Layer::init()==false) {
        return false;
    }
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    // TODO: may create only once in SceneMediator?
    //_background = SceneMediator::getInstance()->getMainBackground();
    _background = MainBackground::create();
    addChild(_background);
    
    //initialize buttons
    _startButton = ui::Button::create("start.png");
    //_startButton = ui::Button::create();
    //_startButton->loadTextures("start.png", "start.png");
    _startButton->setPosition(Vec2(viewSize.width/2, viewSize.height/2+20));
    addChild(_startButton);
    
    _statusButton = ui::Button::create("status.png");
    _statusButton->setPosition(Vec2(viewSize.width/2, viewSize.height/2-100));
    addChild(_statusButton);
    
    _scoreButton = ui::Button::create("score.png");
    _scoreButton->setPosition(Vec2(viewSize.width/2, viewSize.height/2-220));
    addChild(_scoreButton);
    
    _getUnitButton = ui::Button::create("getUnits.png");
    _getUnitButton->setPosition(Vec2(viewSize.width/2, viewSize.height/2-340));
    addChild(_getUnitButton);
    
    _exitButton = ui::Button::create("exit.png");
    _exitButton->setPosition(Vec2(viewSize.width/2, viewSize.height/2-460));
    addChild(_exitButton);

    
    //initialize ui event listener
    
    // TODO: may used TouchListener
    _startButton->addClickEventListener([](Ref* ref) {
        SceneMediator::getInstance()->gotoStageSelectScene();
    });
    _scoreButton->addClickEventListener([](Ref* ref) {
        SceneMediator::getInstance()->gotoStageScoreScene();
    });
    _statusButton->addClickEventListener([](Ref* ref) {
        SceneMediator::getInstance()->gotoStatusScene();
    });
    _getUnitButton->addClickEventListener([](Ref* ref) {
        SceneMediator::getInstance()->gotoGetUnitScene();
    });

    _exitButton->addClickEventListener([](Ref* ref) {
        Director::getInstance()->end();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
        #endif
    });

    
    return true;
}
