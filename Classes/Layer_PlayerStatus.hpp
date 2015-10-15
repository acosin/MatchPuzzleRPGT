//
//  Layer_PlayerStatus.hpp
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "PlayerStatusData.h"

USING_NS_CC;

class Layer_PlayerStatus
{
public:
    static ui::Widget* createItem(PlayerStatusData* data)
    {
        auto node = CSLoader::createNode("ui/Layer_PlayerStatus.csb");
        
        ui::ImageView* playerIcon = dynamic_cast<ui::ImageView*>(node->getChildByName("Image_PlayerIcon"));
        ui::Text* playerName = dynamic_cast<ui::Text*>(node->getChildByName("Text_PlayerName"));
        ui::Text* playerLV = dynamic_cast<ui::Text*>(node->getChildByName("Text_PlayerLv"));
        
        playerIcon->loadTexture(data->playerIconPath);
        playerName->setString(data->playerName);
        playerLV->setString("lv: " + Value(data->playerLevel).asString());
        
        ui::Widget* item = ui::Widget::create();
        item->setContentSize(node->getContentSize());
        item->addChild(node);
        
        return item;
    }
};
