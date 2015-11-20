//
//  Jewel.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"
#include "ElementType.h"

USING_NS_CC;

class Jewel : public Sprite
{
private:
    ElementType _type;
    
    int _x;
    int _y;
    
    bool _isSwaping;
    
public:
    static Jewel* createByType(ElementType type, int x, int y);
    bool init(ElementType type, int x, int y);
    
    
    ElementType getType() { return _type; }
    int getX() { return _x; }
    int getY() { return _y; }
    
    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
    
    bool isSwaping() { return _isSwaping; }
    bool isCrushing() { return _isCrushing; }
    
    void setSwapingState(bool state) { _isSwaping = state; }
    
    void crush();
    
    bool _isCrushing;
    
};
