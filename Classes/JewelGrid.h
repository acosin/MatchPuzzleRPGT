//
//  JewelGrid.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"
#include <vector>

#include "ElementType.h"

#include "JewelGridStatus.h"

USING_NS_CC;
using namespace std;

#define GRID_WIDTH 80 //pixels of a grid: 40x40
#define MOVE_SPEED 0.2

const int FIRST_JEWEL_ID = 0;
const int LAST_JEWEL_ID = int(ElementType::count)-1;

class Jewel;

//The grid container of Jewel Class, including the logic of jewels in this grid
//(0,0) in left bottom, x->right, y->up
class JewelsGrid : public Node
{
public:
    static const std::string eventNameStatusChange;
public:
    static JewelsGrid* create(int row, int col);
    bool init(int row, int col);
    
    void updateMap();
    bool isDeadMap();
    
    void startDispatchStatusChange();
    void stopDispatchStatusChange();
    
    int getStatusXCombo();
    int getStatusYCombo();
    
    
private:
    Jewel* createAJewel(int x, int y);
    bool isJewelLegal(Jewel* jewel, int x, int y); //if match 3,illegal
    void setJewelPixPos(Jewel* jewel, float x, float y); //set actual pos of Jewel Sprite in the game
    
    //operation of Jewel
    void swapJewels(Jewel *jewelA, Jewel *jewelB);
    void swapJewelToNewPos(Jewel* jewel);
    
    void refreshJewelsGrid();
    void refreshJewelsToNewPos(int col);
    
private:
    //event callback
    bool onTouchBegan(Touch*, Event*);
    void onTouchMoved(Touch*, Event*);
    
private:
    //game logic
    bool canCrush(); //judge whether current stage can be crushed
    void goCrush();
    
    //catch function, check whether crushing is finish
    void onJewelsSwaping(float dt);
    void onJewelsSwapingBack(float dt);
    void onJewelsCrushing(float dt);
    void onJewelsRefreshing(float dt);
    
    bool isDispatchStatusChange = false;
    void dispatchEventStatusChange();
    
public:
    int getRow() { return m_row; }
    int getCol() { return m_col; }
    
private:
    int m_row;
    int m_col;
    
    Jewel* m_jewelSelected;
    Jewel* m_jewelSwapped;
    
    vector<vector<Jewel*>> m_JewelsBox;
    Vector<Jewel*> m_crushJewelBox;
    Vector<Jewel*> m_newJewelBox;
    
    JewelGridStatus* m_status;
    vector<MatchCombo*> tempComboes;
};
