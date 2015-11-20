//
//  StageClearScene.cpp
//  MatchPuzzleRPGT
//
//

#include "StageClearLayer.h"

#include "SimpleGrowthStrategyStageClear.hpp"
#include "SimpleScoreStageClearStrategy.hpp"

#include "GameStageController.h"


int StageClearLayer::BonusKillAllEnemies = 1000;

StageClearLayer::StageClearLayer()
{
    
}

StageClearLayer::~StageClearLayer()
{
    
}

bool StageClearLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    _layout = CSLoader::createNode("ui/StageClearLayer.csb");
    _layout->setName("LAYOUT");
    
    _clearInfo = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_clearInfo"));
    _textScore = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_score"));
    _textScoreStage = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_score_stage"));
    _textScoreEnemy = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_score_enemy"));
    _textScoreTotal = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_score_total"));
    _textGrowthPlayer = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_growth_player"));
    _textGrowthPlayerResult = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_growth_playerResult"));
    
    this->addChild(_layout);
    
    _growthStrategyStageClear = new SimpleGrowthStrategyStageClear();
    _scoreStageClearStrategy = new SimpleScoreStageClearStrategy();

    return true;
}

bool StageClearLayer::initWithData(StageClearData *data)
{
    CCLOG("StageClearLayer: handle StageClearData");
    _clearData = data;
    
    
    auto scoreBasic = _clearData->score;
    _textScore->setString("Basic Score: " + Value(scoreBasic).asString());
    auto scoreStage = _scoreStageClearStrategy->getScoreToAdd(_clearData->stageData);
    _textScoreStage->setString("Stage Bonus: " +
                               Value(scoreStage).asString());
    int scoreEnemies = 0;
    if (_clearData->type == ClearStageConditionType::NO_ENEMY) {
        scoreEnemies = BonusKillAllEnemies;
        _textScoreEnemy->setString("Kill All Enemies Bonus: " +
                                   Value(scoreEnemies).asString());
    } else {
        _textScoreEnemy->setVisible(false);
    }
    auto totalScore = scoreBasic + scoreStage + scoreEnemies;
    _textScoreTotal->setString("Total Score: " + Value(totalScore).asString());
    
    handleGrowthAndScore(totalScore);
    
    return true;
}

void StageClearLayer::handleGrowthAndScore(int totalScore)
{
    // -- growth for player--
    auto addExp = _growthStrategyStageClear->getPlayerExp(_clearData);
    _textGrowthPlayer->setString("Player Exp: +" + Value(addExp).asString());
    
    auto currentExp = _clearData->playerExp;
    auto newExp = currentExp;
    auto currentLevel = _clearData->playerLevel;
    auto newLevel = _growthStrategyStageClear->getNewPlayerLevel(currentLevel, newExp, addExp);
    
    if (newLevel != currentLevel) {
        CCLOG("Level up! %d -> %d", currentLevel, newLevel);
        auto str = "Level up!\n Lv." + Value(currentLevel).asString()+ " -> Lv."+Value(newLevel).asString();
        _textGrowthPlayerResult->setString(str);
    } else {
        CCLOG("Exp up! %d -> %d", currentExp, newExp);
        auto str = "Exp: " + Value(currentExp).asString()+ " -> "+Value(newExp).asString();
        _textGrowthPlayerResult->setString(str);
    }
    
    // -- growth for UnitSortie
    
    // persistence
    handleStageClear(newLevel, newExp, totalScore);
}

void StageClearLayer::handleStageClear(int newPlayerLevel, int newPlayerExp, int score)
{
    dispatchGrowthEvent(newPlayerLevel, newPlayerExp);
    dispatchSaveScoreEvent(score);
}

void StageClearLayer::dispatchGrowthEvent(int newPlayerLevel, int newPlayerExp)
{
    auto growthData = new GrowthDataStageClear();
    growthData->newPlayerLevel = newPlayerLevel;
    growthData->newPlayerExp = newPlayerExp;
    growthData->growthStrategy = _growthStrategyStageClear;
    growthData->clearData = _clearData;
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(GameStageController::EventNameProcessGrowth, growthData);
    
}

void StageClearLayer::dispatchSaveScoreEvent(int score)
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    //TODO: may need to guarantee safa memory access (&score) here!!!!
    dispatcher->dispatchCustomEvent(GameStageController::EventNameSaveScore, &score);
}
