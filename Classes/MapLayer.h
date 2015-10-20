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
    
public:
    MapLayer();
    virtual ~MapLayer();
    
    CREATE_FUNC(MapLayer);
    
    static MapLayer* create(const std::string &mapFilename);
    
    virtual bool init();
    bool initMap(const std::string &mapFilename);
};
