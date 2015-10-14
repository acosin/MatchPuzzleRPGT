//
//  ListItem_UnitRecord.h
//  MatchPuzzleRPGT
//
//

#ifndef ListItem_UnitRecord_h
#define ListItem_UnitRecord_h


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
        ui::Widget* item = ui::Widget::create();
        auto node = CSLoader::createNode("ui/UnitRecordItem.csb");
        ui::ImageView* unitIcon = dynamic_cast<ui::ImageView*>(node->getChildByName("Image_unitIcon"));
        ui::Text* unitInfo = dynamic_cast<ui::Text*>(node->getChildByName("Text_unitInfo"));
        unitIcon->loadTexture(record->unitdata.unitIconPath);
        unitInfo->setString(record->unitdata.unitName);
        item->addChild(node);
        return item;
    }
};


#endif /* ListItem_UnitRecord_h */
