//
//  ListItem_UnitRecord.cpp
//  MatchPuzzleRPGT

#include "ListItem_UnitRecord.h"


std::string ListItem_UnitRecord::ImageFile_checkboxNormal = "ui/Resources/checkbox_normal.png";
std::string ListItem_UnitRecord::ImageFile_checkboxDisable = "ui/Resources/checkbox_disable.png";
Texture2D* ListItem_UnitRecord::imageCheckboxNormal = nullptr;
Texture2D* ListItem_UnitRecord::imageCheckboxDisable = nullptr;

void ListItem_UnitRecord::loadImageOnce()
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

ListItem_UnitRecord* ListItem_UnitRecord::createListItem(UnitOfPlayerRecord* record)
{
    ListItem_UnitRecord::loadImageOnce();
    
    auto item = ListItem_UnitRecord::create();
    auto node = CSLoader::createNode("ui/ListItem_UnitRecord.csb");
    
    ui::ImageView* unitIcon = dynamic_cast<ui::ImageView*>(node->getChildByName("Image_unitIcon"));
    ui::Text* unitInfo = dynamic_cast<ui::Text*>(node->getChildByName("Text_unitInfo"));
    unitIcon->loadTexture(record->unitdata.unitIconPath);
    unitInfo->setString(record->unitdata.unitName);
    
    item->_checkboxIsDefault = dynamic_cast<ui::CheckBox*>(node->getChildByName("CheckBox_isDefault"));
    item->_checkboxIsDefault->loadTextureFrontCross(ListItem_UnitRecord::ImageFile_checkboxNormal);
    item->_checkboxIsDefault->loadTextureFrontCrossDisabled(ListItem_UnitRecord::ImageFile_checkboxDisable);
    
    
    //TODO: only for debug, remove later
    if (item->_checkboxIsDefault == NULL || item->_checkboxIsDefault == nullptr) {
        CCLOG("ListItem_UnitRecord::checkbox null!");
    }
    
    
    item->_checkboxIsDefault->setSelected(record->isSortie);
    
    item->setContentSize(node->getContentSize());
    item->addChild(node);
    
    item->type = record->unitdata.elementType;
    return item;
}

void ListItem_UnitRecord::setSelected(bool is_select)
{
    isSelect = is_select;
    _checkboxIsDefault->setSelected(is_select);
}