//
//  ListItem_UnitRecord.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "UnitOfPlayerRecord.h"

USING_NS_CC;

class ListItem_UnitRecord
{
public:
    static ui::Widget* createListItem(UnitOfPlayerRecord* record)
    {
        auto node = CSLoader::createNode("ui/ListItem_UnitRecord.csb");
        
        ui::ImageView* unitIcon = dynamic_cast<ui::ImageView*>(node->getChildByName("Image_unitIcon"));
        ui::Text* unitInfo = dynamic_cast<ui::Text*>(node->getChildByName("Text_unitInfo"));
        unitIcon->loadTexture(record->unitdata.unitIconPath);
        unitInfo->setString(record->unitdata.unitName);
        
        ui::Widget* item = ui::Widget::create();
        //item->setSize(node->getSize());
        //item->setSizePercent(Vec2(96.0, 60.0));
        //item->setSize(Size(100,90));
        //item->setSizePercent(Vec2(900.0, 1000.0));
        //node->setPosition(Vec2(0.5, 0.5));
        item->setContentSize(node->getContentSize());
        item->addChild(node);
        return item;
    }
};
