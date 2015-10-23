//
//  AnalogStick.hpp
//  MatchPuzzleRPGT

#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum class TagForStickPart {
    tag_stick,
    tag_outer,
};


enum class TagForDirection {
    stay,
    right,
    up,
    left,
    down,
};

class AnalogStick : public Layer
{
public:
    AnalogStick();
    ~AnalogStick();
    
    //创建摇杆(摇杆的操作题图片资源名，摇杆背景图片资源名，起始坐标)
    static AnalogStick* createStick(const std::string &stickImageName,const std::string &outerImageName, const Vec2 &pos);
    //启动摇杆(显示摇杆、监听摇杆触屏事件)
    void startStick();
    //停止摇杆(隐藏摇杆，取消摇杆的触屏监听)
    void stopStick();
    //判断控制杆方向，用来判断精灵上、下、左、右运动
    int stickDirection;
    //当前人物行走方向,用来判断精灵的朝向，精灵脸朝右还是朝左
    //bool rocketRun;
    CREATE_FUNC(AnalogStick);
private:
    //自定义初始化函数
    void stickInit(const std::string &stickImageName,const std::string &outerImageName, const Vec2 &pos);
    //是否可操作摇杆
    bool isCanMove;
    //获取当前摇杆与用户触屏点的角度
    float getRad(Vec2 pos1,Vec2 pos2);
    //摇杆背景的坐标
    Vec2 stickOuterPosition;
    //摇杆背景的半径
    float stickOuterRadius;
    //触屏事件
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    
};
