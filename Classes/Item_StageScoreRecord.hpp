//
//  Item_StageScoreRecord.hpp
//  MatchPuzzleRPGT
//


#pragma once

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "StageScoreRecord.h"

USING_NS_CC;

class Item_StageScoreRecord
{
public:
    static ui::Widget* createItem(StageScoreRecord* record)
    {
        auto node = CSLoader::createNode("ui/Item_StageScoreRecord.csb");
        
        ui::ImageView* stageIcon = dynamic_cast<ui::ImageView*>(node->getChildByName("Image_stageIcon"));
        ui::Text* stageName = dynamic_cast<ui::Text*>(node->getChildByName("Text_stageName"));
        ui::Text* bestScore = dynamic_cast<ui::Text*>(node->getChildByName("Text_bestScore"));

        stageIcon->loadTexture(record->getStageIconPath());
        stageName->setString(record->getStageName());
        bestScore->setString("best: "+Value(record->getBestScore()).asString());
        
        ui::Widget* item = ui::Widget::create();
        item->setContentSize(node->getContentSize());
        item->addChild(node);
        return item;
    }
};
