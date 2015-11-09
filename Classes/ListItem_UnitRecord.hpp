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
    static std::string ImageFile_checkboxNormal;
    static std::string ImageFile_checkboxDisable;
    static Texture2D* imageCheckboxNormal;
    static Texture2D* imageCheckboxDisable;
public:
    ui::CheckBox *_checkboxIsDefault = nullptr;
    
public:
    CREATE_FUNC(ListItem_UnitRecord);
    
    static void loadImageOnce()
    {
        if (ListItem_UnitRecord::imageCheckboxNormal == nullptr) {
            Director::getInstance()->getTextureCache()->addImage(ListItem_UnitRecord::ImageFile_checkboxNormal);
            ListItem_UnitRecord::imageCheckboxNormal = Director::getInstance()->getTextureCache()->getTextureForKey(ListItem_UnitRecord::ImageFile_checkboxNormal);
        }
        
        if (ListItem_UnitRecord::imageCheckboxDisable== nullptr) {
            Director::getInstance()->getTextureCache()->addImage(ListItem_UnitRecord::ImageFile_checkboxDisable);
            ListItem_UnitRecord::imageCheckboxDisable = Director::getInstance()->getTextureCache()->getTextureForKey(ListItem_UnitRecord::ImageFile_checkboxDisable);
        }
    }
    
    static ui::Widget* createListItem(UnitOfPlayerRecord* record)
    {
        //ListItem_UnitRecord::loadImageOnce();
        
        auto item = ListItem_UnitRecord::create();
        auto node = CSLoader::createNode("ui/ListItem_UnitRecord.csb");
        
        ui::ImageView* unitIcon = dynamic_cast<ui::ImageView*>(node->getChildByName("Image_unitIcon"));
        ui::Text* unitInfo = dynamic_cast<ui::Text*>(node->getChildByName("Text_unitInfo"));
        unitIcon->loadTexture(record->unitdata.unitIconPath);
        unitInfo->setString(record->unitdata.unitName);
        /*
        item->_checkboxIsDefault = dynamic_cast<ui::CheckBox*>(node->getChildByName("CheckBox_isDefault"));
        item->_checkboxIsDefault->loadTextures(ListItem_UnitRecord::ImageFile_checkboxNormal,//const std::string &background,
                                               ListItem_UnitRecord::ImageFile_checkboxNormal,
                                               ListItem_UnitRecord::ImageFile_checkboxNormal,//const std::string &cross,
                                               ListItem_UnitRecord::ImageFile_checkboxDisable,
                                               ListItem_UnitRecord::ImageFile_checkboxDisable);
        */
        
        //TODO: only for debug, remove later
        if (item->_checkboxIsDefault == NULL || item->_checkboxIsDefault == nullptr) {
            CCLOG("ListItem_UnitRecord::checkbox null!");
        }
        
        item->setContentSize(node->getContentSize());
        item->addChild(node);
        return item;
    }
    
    
};

/*
std::string ListItem_UnitRecord::ImageFile_checkboxNormal = "ui/Resources/checkbox_normal.png";
std::string ListItem_UnitRecord::ImageFile_checkboxDisable = "ui/Resources/checkbox_disable.png";
Texture2D* ListItem_UnitRecord::imageCheckboxNormal = nullptr;
Texture2D* ListItem_UnitRecord::imageCheckboxDisable = nullptr;
 */
