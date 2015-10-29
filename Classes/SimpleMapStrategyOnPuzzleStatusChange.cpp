//
//  SimpleMapStrategyOnPuzzleStatusChange.cpp
//  MatchPuzzleRPGT
//

#include "SimpleMapStrategyOnPuzzleStatusChange.h"

#include "EnemyNode.h"

void SimpleMapStrategyOnPuzzleStatusChange::exec(MapController *c, PuzzleStatusChangeData *data)
{
    CCLOG("dmageEnemy: x(%d) y(%d)", data->xCombo, data->yCombo);
    
    //firstly, damage handling for enemyItem
    //[Strategy] here damage enemies around the player
    auto enemies = c->getEnemyAround(c->getPlayerX(), c->getPlayerY());
    for (auto enemy : enemies) {
        auto enemyItem = enemy.second;
        EnemyNode* enemyNode = dynamic_cast<EnemyNode*>(enemyItem->getNode());
        auto currentHP = enemyItem->getCurrentHP();
        int damage;
        if (enemyItem->getX() == c->getPlayerX()) {
            damage = data->xCombo;
            //damage = data->xCombo - 1;
        } else if (enemyItem->getY() == c->getPlayerY()) {
            damage = data->yCombo;
            //damage = data->yCombo -1;
        }
        auto afterHP = enemyItem->getDamaged(damage);
        float totalHP = (float)enemyItem->getTotalHP();
        enemyNode->animateFromTo(durationEnemyDamageAnimation,
                                 currentHP/totalHP*100,
                                 afterHP/totalHP*100);
        //death handling
        if (enemyItem->isDead()) {
            enemyNode->showDeadAnimation();
            c->removeMapItem(enemyItem->getID());
        }
    }
}