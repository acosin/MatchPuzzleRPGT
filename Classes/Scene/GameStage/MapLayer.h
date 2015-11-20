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
public:
    static const std::string EventNameMapTounch;
private:
    TMXLayer* _background;
    Node* _player;
    Vector<Sprite*> _enemies;
    TMXLayer* _meta;
    
public:
    
    TMXTiledMap* _tileMap;
    
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
    void initPlayer(Sprite* player);
    bool movePlayerTo(int x, int y);
    
    Vec2 convertToPixelPos(const Vec2 &mapPos);
    Vec2 convertToMapPos(const Vec2 &pixelPos);
    
    void scaleAsTileSize(Node* node);
    bool moveNodeOnMap(Node* node, int x, int y);
    //bool moveSpriteOnMap(Sprite* sprite, int x, int y);
    
    bool isGoalPos(int x, int y);
    
    void enableTouch();
    void disableTouch();
    
private:
    void setViewPointCenter(Point position);
    
    
    void onTouchEnded(Touch *touch, Event *unused_event);
    void dispatchEventMapTouch(Point &mapPos);
};
