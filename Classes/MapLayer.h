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
    Vector<Sprite*> _enemies;
    
public:
    MapLayer();
    virtual ~MapLayer();
    
    CREATE_FUNC(MapLayer);
    
    static MapLayer* create(const std::string &mapFilename, const std::string &playerFilename); //TODO: remove later
    static MapLayer* create(const std::string &mapFilename);
    
    virtual bool init();
    bool initMap(const std::string &mapFilename, const std::string &playerFilename); //TODO: remove later
    bool initMap(const std::string &mapFilename);
    bool initPlayer(const std::string &playerFilename);    
    void movePlayerTo(int x, int y);
    
    Vec2 convertToPixelPos(const Vec2 &mapPos);
    Vec2 convertToMapPos(const Vec2 &pixelPos);
    
    
private:
    void setViewPointCenter(Point position);
    
    
    void onTouchEnded(Touch *touch, Event *unused_event);
};
