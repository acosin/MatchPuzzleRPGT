//
//  ListItem_UnitRecord.hpp
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "UnitOfPlayerRecord.h"

USING_NS_CC;

class ListItem_UnitRecord : public ui::Widget
{
public:
    ui::CheckBox *_checkboxIsDefault;
public:
    CREATE_FUNC(ListItem_UnitRecord);
    
    static ui::Widget* createListItem(UnitOfPlayerRecord* record)
    {
        auto item = ListItem_UnitRecord::create();
        auto node = CSLoader::createNode("ui/ListItem_UnitRecord.csb");
        
        ui::ImageView* unitIcon = dynamic_cast<ui::ImageView*>(node->getChildByName("Image_unitIcon"));
        ui::Text* unitInfo = dynamic_cast<ui::Text*>(node->getChildByName("Text_unitInfo"));
        unitIcon->loadTexture(record->unitdata.unitIconPath);
        unitInfo->setString(record->unitdata.unitName);
        item->_checkboxIsDefault = dynamic_cast<ui::CheckBox*>(node->getChildByName("CheckBox_isDefault"));
        
        //TODO: only for debug, remove later
        if (item->_checkboxIsDefault == NULL || item->_checkboxIsDefault == nullptr) {
            CCLOG("ListItem_UnitRecord::checkbox null!");
        }
        
        item->setContentSize(node->getContentSize());
        item->addChild(node);
        return item;
    }
    
    
};
