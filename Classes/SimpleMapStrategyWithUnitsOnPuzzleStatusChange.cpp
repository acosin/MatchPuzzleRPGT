//
//  SimpleMapStrategyWithUnitsOnPuzzleStatusChange.cpp
//  MatchPuzzleRPGT
//


#include "SimpleMapStrategyWithUnitsOnPuzzleStatusChange.h"

#include "EnemyNode.h"

SimpleMapStrategyWithUnitsOnPuzzleStatusChange::SimpleMapStrategyWithUnitsOnPuzzleStatusChange()
: IMapStrategyOnPuzzleStatusChange()
{
    for (int type = 0; type < (int)ElementType::count; type++) {
        auto typeE = (ElementType)type;
        unitElementDamage[typeE] = 0;
    }
}

SimpleMapStrategyWithUnitsOnPuzzleStatusChange::~SimpleMapStrategyWithUnitsOnPuzzleStatusChange()
{
    unitElementDamage.clear();
}

void SimpleMapStrategyWithUnitsOnPuzzleStatusChange::exec(MapController *c, PuzzleStatusChangeData *data)
{
    CCLOG("dmageEnemy: x(%d) y(%d)", data->xCombo, data->yCombo);
    
    //firstly, damage handling for enemyItem
    //[Strategy] here damage enemies around the player
    auto enemies = c->getEnemyAround(c->getPlayerX(), c->getPlayerY());
    for (auto enemy : enemies) {
        auto enemyItem = enemy.second;
        EnemyNode* enemyNode = dynamic_cast<EnemyNode*>(enemyItem->getNode());
        auto currentHP = enemyItem->getCurrentHP();
        int damage = 0;
        if (enemyItem->getX() == c->getPlayerX()) {
            for (int type = 0; type < (int)ElementType::count; type++) {
                auto typeE = (ElementType)type;
                auto unitRecord = data->getUnitRecordOfType(typeE);
                //TODO: may use other atk equation!!!
                auto atk = unitRecord->unitdata->atk + unitRecord->level;
                auto matchX = data->getMatchCountX(typeE);
                auto newDamage = matchX * atk;
                damage += newDamage;
                unitElementDamage[typeE] += newDamage;
            }
        } else if (enemyItem->getY() == c->getPlayerY()) {
            for (int type = 0; type < (int)ElementType::count; type++) {
                auto typeE = (ElementType)type;
                auto unitRecord = data->getUnitRecordOfType(typeE);
                auto atk = unitRecord->unitdata->atk + unitRecord->level;
                auto matchY = data->getMatchCountY(typeE);
                auto newDamage = matchY * atk;
                damage += newDamage;
                unitElementDamage[typeE] += newDamage;            }
        }
        auto afterHP = enemyItem->getDamaged(damage);
        float totalHP = (float)enemyItem->getTotalHP();
        CC_ASSERT(totalHP!=0);
        enemyNode->animateFromTo(durationEnemyDamageAnimation,
                                 currentHP/totalHP*100,
                                 afterHP/totalHP*100);
        
        //death handling
        //TODO: process like this cannot guarantee synchonization of the end of the damage animation and the start of the dead animation
        if (enemyItem->isDead()) {
            auto sequence = Sequence::create(DelayTime::create(durationEnemyDamageAnimation), CallFunc::create([enemyNode,enemyItem,c](){
                enemyNode->showDeadAnimation();
                // NOTE: before remove enemyItem, handling score change
                c->dispatchEnemyDeadEvent(enemyItem);
                // end score handling
                c->removeMapItem(enemyItem->getID());
            }), NULL);
            enemyNode->runAction(sequence);
        }
        
    }
    
}

int SimpleMapStrategyWithUnitsOnPuzzleStatusChange::getUnitElementDamage(ElementType type)
{
    return unitElementDamage[type];
}