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
    bool isSelect = false;
    int index = -1;
    ElementType type;
    
public:
    CREATE_FUNC(ListItem_UnitRecord);
    
    static void loadImageOnce();
    static ListItem_UnitRecord* createListItem(UnitOfPlayerRecord* record);
    
    void setSelected(bool is_select);
};



