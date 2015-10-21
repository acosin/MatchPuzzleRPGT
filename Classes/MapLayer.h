//
//  MapLayer.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class MapLayer : public cocos2d::Layer
{
private:
    TMXTiledMap* _tileMap;
    TMXLayer* _background;
    Sprite* _player;
    
public:
    MapLayer();
    virtual ~MapLayer();
    
    CREATE_FUNC(MapLayer);
    
    static MapLayer* create(const std::string &mapFilename, const std::string &playerFilename);
    
    virtual bool init();
    bool initMap(const std::string &mapFilename, const std::string &playerFilename);
    
    void movePlayerTo(int x, int y);
    
private:
    void setViewPointCenter(Point position);
};
