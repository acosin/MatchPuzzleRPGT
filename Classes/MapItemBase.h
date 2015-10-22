//
//  MapItemBase.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

#include "IMapItem.h"

USING_NS_CC;

class MapItemBase : public IMapItem
{
protected:
    uint32_t id;
    int x;
    int y;
    bool movable;
    MapItemType type;
    std::string imagePath;
    
public:
    MapItemBase();
    MapItemBase(int x, int y, bool movable, MapItemType type, const std::string &path);
    ~MapItemBase();
    
    uint32_t getID() override;
    void setID(uint32_t id) override;
    int getX() override;
    int getY() override;
    void setX(int x) override;
    void setY(int y) override;
    void setXY(int x, int y) override;
    bool isMovable() override;
    void setMovable(bool flag) override;
    MapItemType getType() override;
    void setType(MapItemType type) override;
    std::string getImagePath() override;
    void setImagePath(const std::string &path) override;
};
