//
//  JewelGridStatus.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include <set>
#include <vector>

#include "ElementType.h"
#include "Jewel.h"

class JewelInfo
{
public:
    int x,y;
    ElementType type;
public:
    JewelInfo(int x,int y, ElementType type) {
        set(x, y, type);
    }
    
    void set(int x, int y, ElementType type) {
        this->x = x;
        this->y = y;
        this->type = type;
    }
    
    // only check pos
    bool operator==(const JewelInfo& rhs) const
    {
        return (x == rhs.x && y == rhs.y);
    }
    
    bool operator<(const JewelInfo& rhs) const
    {
        return (x < rhs.x && y < rhs.y);
    }
    
    static JewelInfo* createJewelInfo(Jewel* jewel)
    {
        return new JewelInfo(jewel->getX(),
                             jewel->getY(),
                             jewel->getType());
    }
};


//TODO: may use other storing style
class MatchedJewels
{
public:
    //NOTE: store by the order [x][y]
    std::set<JewelInfo> jewelset;
    std::set<int> rows;
    std::set<int> cols;
public:
    static MatchedJewels* createMatchRow(int row, int startCol, int endCol, ElementType type);
    static MatchedJewels* createMatchCol(int col, int startRow, int endRow, ElementType type);
    
    void addMatchRowIgnoreDuplication(int row, int startCol, int endCol, ElementType type);
    void addMatchColIgnoreDuplication(int col, int startRow, int endRow, ElementType type);
    
    int getRowCount();
    int getColCount();
    ElementType getType();
};

class MatchCombo
{
public:
    std::vector<MatchedJewels*> matches;
public:
    int getRowCount();
    int getColCount();
    int getRowOfTypeCount(ElementType type);
    int getColOfTypeCount(ElementType type);
    void addMatch(MatchedJewels* match);
};

class JewelGridStatus
{
public:
    bool isCrushing = false;
    int comboCount = 0;
    std::vector<MatchCombo*> comboes;
    
public:
    JewelGridStatus();
    ~JewelGridStatus();
    
    int getRowCount();
    int getColCount();
    int getRowOfTypeCount(ElementType type);
    int getColOfTypeCount(ElementType type);
    
    void addCombo(MatchCombo* combo);
    void clearCombo();
};
