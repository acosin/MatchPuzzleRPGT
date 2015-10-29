//
//  GameStageHUD.cpp
//  MatchPuzzleRPGT
//
//  Created by Suiyan Li on 15/10/29.
//
//

#include "GameStageHUD.h"

USING_NS_CC;

GameStageHUD::GameStageHUD()
{
    
}

GameStageHUD::~GameStageHUD()
{
    
}

Scene* GameStageHUD::createScene()
{
    auto scene = Scene::create();
    auto layer = GameStageHUD::create();

    scene->addChild(layer);

    return scene;
}

bool GameStageHUD::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    return true;
}


#pragma mark - Private methods

