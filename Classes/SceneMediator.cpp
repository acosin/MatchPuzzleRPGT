//
//  SceneMediator.cpp
//  MatchPuzzleRPGT
//
//

#include "SceneMediator.h"

#include "HomeScene.h"
#include "StatusScene.h"

SceneMediator* SceneMediator::_instance = nullptr;
MainBackground* SceneMediator::_mainBackground = nullptr;

SceneMediator* SceneMediator::getInstance()
{
    if (_instance == nullptr) {
        _instance = new SceneMediator();
    }
    
    return _instance;
}

// TODO: not used now, MAY MAINTAIN ONE HERE
MainBackground* SceneMediator::getMainBackground()
{
    if (_mainBackground == nullptr) {
        _mainBackground = MainBackground::create();
    }
    return _mainBackground;
}

void SceneMediator::gotoHomeScene()
{
    auto scene = HomeScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
}

void SceneMediator::gotoStageSelectScene()
{
    
}

void SceneMediator::gotoGameStageScene()
{
    
}

void SceneMediator::gotoStageScoreScene()
{
    
}

void SceneMediator::gotoStatusScene()
{
    
    auto scene = StatusScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
}