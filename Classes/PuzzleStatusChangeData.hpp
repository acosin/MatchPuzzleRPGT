//
//  JewelStatusChangeData.hpp
//  MatchPuzzleRPGT
//

#pragma once

#include "cocos2d.h"
#include <map>
#include "ElementType.h"
#include "JewelGridStatus.h"

USING_NS_CC;

class PuzzleStatusChangeData : public Ref
{
private:
    std::map<ElementType, int> matchCountX, matchCountY;
    int comboCount;
public:
    int xCombo;
    int yCombo;

    //JewelGridStatus *status;
public:
    PuzzleStatusChangeData() {
        for (int type = 0; type<(int)ElementType::count; type++) {
            matchCountX[(ElementType)type] = 0;
            matchCountY[(ElementType)type] = 0;
        }
        comboCount = 0;
        xCombo = 0;
        yCombo = 0;
    }
    
    int getMatchCountX(ElementType type) {
        return matchCountX[type];
    }
    void setMatchCountX(ElementType type, int count) {
        matchCountX[type] = count;
    }
    int getMatchCountY(ElementType type) {
        return matchCountY[type];
    }
    void setMatchCountY(ElementType type, int count) {
        matchCountY[type] = count;
    }
    
    int getComboCount() {
        return comboCount;
    }
    
    void init(const JewelGridStatus *status) {
        for (int type = 0; type<(int)ElementType::count; type++) {
            auto xCount = status->getColOfTypeCount((ElementType)type);
            matchCountX[(ElementType)type] = xCount;
            xCombo += xCount;
            auto yCount = status->getRowOfTypeCount((ElementType)type);
            matchCountY[(ElementType)type] = yCount;
            yCombo += yCount;
        }
        comboCount = status->getComboCount();
    }
    
    static PuzzleStatusChangeData* create(const JewelGridStatus *status) {
        auto data = new PuzzleStatusChangeData();
        data->init(status);
        return data;
    }
};