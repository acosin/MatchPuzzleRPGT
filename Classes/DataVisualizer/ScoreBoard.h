//
//  ScoreBoard.h
//  MatchPuzzleRPGT
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "HealthBar.h"

USING_NS_CC;

class ScoreBoard : public __LayerRGBA
{
private:
    int _score;
    
    ui::Text* _text;
protected:
    
public:
    ScoreBoard();
    ~ScoreBoard();
    
    CREATE_FUNC(ScoreBoard);
    virtual bool init();
    static ScoreBoard* createScoreBoard(const std::string &enemyImage);
    
    void setScore(int score);
    int getScore();
};
