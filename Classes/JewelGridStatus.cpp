//
//  JewelGridStatus.cpp
//  MatchPuzzleRPGT
//
//

#include "JewelGridStatus.h"

//NOTE: not check >0 here, check startCol <= endCol
MatchedJewels* MatchedJewels::createMatchRow(int row, int startCol, int endCol, ElementType type)
{
    if (startCol > endCol)
        return nullptr;
    
    auto ret = new MatchedJewels();
    ret->addMatchRowIgnoreDuplication(row, startCol, endCol, type);
    return ret;
}

MatchedJewels* MatchedJewels::createMatchCol(int col, int startRow, int endRow, ElementType type)
{
    if (startRow > endRow)
        return nullptr;
    
    auto ret = new MatchedJewels();
    ret->addMatchColIgnoreDuplication(col, startRow, endRow, type);
    return ret;
}

void MatchedJewels::addMatchRowIgnoreDuplication(int row, int startCol, int endCol, ElementType type)
{
    if (startCol > endCol) {
        return;
    }
    
    for (int i = startCol; i <= endCol; i++) {
        jewelset.insert(JewelInfo(i, row, type));
    }
    rows.insert(row);
}

void MatchedJewels::addMatchColIgnoreDuplication(int col, int startRow, int endRow, ElementType type)
{
    if (startRow > endRow)
        return;
    
    for (int i = startRow; i <= endRow; i++) {
        jewelset.insert(JewelInfo(col, i, type));
    }
    cols.insert(col);
}

int MatchedJewels::getRowCount()
{
    return rows.size();
}

int MatchedJewels::getColCount()
{
    return cols.size();
}

ElementType MatchedJewels::getType()
{
    return (*jewelset.begin()).type;
}

// -- MatchCombo --

int MatchCombo::getRowCount()
{
    int ret = 0;
    for (auto match : matches) {
        ret += match->getRowCount();
    }
    return ret;
}

int MatchCombo::getColCount()
{
    int ret = 0;
    for (auto match : matches) {
        ret += match->getColCount();
    }
    return ret;
}

int MatchCombo::getRowOfTypeCount(ElementType type)
{
    int ret = 0;
    for (auto match : matches) {
        if (match->getType() == type) {
            ret += match->getRowCount();
        }
    }
    return ret;
}

int MatchCombo::getColOfTypeCount(ElementType type)
{
    int ret = 0;
    for (auto match : matches) {
        if (match->getType() == type) {
            ret += match->getColCount();
        }
    }
    return ret;
}

void MatchCombo::addMatch(MatchedJewels* match)
{
    matches.push_back(match);
}

int MatchCombo::getMatchedCount()
{
    return (int)matches.size();
}

// -- JewelGridStatus --

JewelGridStatus::JewelGridStatus():
isCrushing(false),
comboCount(0)
{
    
}

JewelGridStatus::~JewelGridStatus()
{
    
}

int JewelGridStatus::getRowCount()
{
    int ret = 0;
    for (auto combo : comboes) {
        ret += combo->getRowCount();
    }
    return ret;
}

int JewelGridStatus::getColCount()
{
    int ret = 0;
    for (auto combo : comboes) {
        ret += combo->getColCount();
    }
    return ret;
}

int JewelGridStatus::getRowOfTypeCount(ElementType type)
{
    int ret = 0;
    for (auto combo : comboes) {
        ret += combo->getRowOfTypeCount(type);
    }
    return ret;
}

int JewelGridStatus::getColOfTypeCount(ElementType type)
{
    int ret = 0;
    for (auto combo : comboes) {
        ret += combo->getColOfTypeCount(type);
    }
    return ret;
}

void JewelGridStatus::addCombo(MatchCombo *combo)
{
    comboes.push_back(combo);
}

//TODO
void JewelGridStatus::clearCombo()
{
    //TODO: need more for memory management
    comboes.clear();
}

