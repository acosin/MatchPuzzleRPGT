//
//  GameStageScene.cpp
//  MatchPuzzleRPGT
//
//

#include "GameStageScene.h"
#include "SimpleScorePuzzleStrategy.hpp"
#include "SimpleScoreEnemyStrategy.hpp"

GameStageScene::GameStageScene():
_layout(nullptr),
_puzzleLayout(nullptr),
_puzzleEffectLayout(nullptr),
_mapLayout(nullptr),
_background(nullptr),
_homeButton(nullptr),
_exitButton(nullptr),
_selectStageButton(nullptr),
_stageID(0),
_currentStageData(nullptr),
_currentStageScore(nullptr),
_stageManager(nullptr),
_controller(nullptr),
_jewelsGrid(nullptr),
_mapLayer(nullptr),
_scoreBoard(nullptr),
_scorePuzzleStrategy(nullptr),
_scoreEnemyStrategy(nullptr)
{
    
}

GameStageScene::~GameStageScene()
{
    removeEventJewelGridStatusChange();
    removeEventStageCLear();
    removeEventFinishComboes();
    removeEventEnemyDead();
}

bool GameStageScene::init()
{
    if (Layer::init()==false) {
        return false;
    }
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    //NOTE: should load texture before creating Jewel class!
    LoadTexture();
    
    _layout = CSLoader::createNode("ui/GameStageScene.csb");
    _layout->setName("LAYOUT");
    
    // TODO: may create only once in SceneMediator?
    //_background = SceneMediator::getInstance()->getMainBackground();
    _background = MainBackground::create();
    _layout->getChildByName("ImageView_background")->addChild(_background);
    
    
    _puzzleLayout = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_puzzle"));
    _puzzleEffectLayout = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_puzzle_stage_effect"));
    _puzzleEffectLayout->setVisible(false);
    //TODO: may use some animation here
    _puzzleEffectLayout->setBackGroundImage("attack.png");
    _mapLayout = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_map"));
    
    _textXcombo = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_xCombo"));
    _textYcombo = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_yCombo"));
    _textXcombo->setVisible(false);
    _textYcombo->setVisible(false);
    hideElementXYCount();
    
    _homeButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_backHome"));
    _exitButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_exit"));
    _selectStageButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_selectStage"));
    
    auto scorePanel = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_score"));
    _scoreBoard = ScoreBoard::create();
    _scoreBoard->setScale(scorePanel->getContentSize().width/_scoreBoard->getContentSize().width,
                          scorePanel->getContentSize().height/_scoreBoard->getContentSize().height);
    _scoreBoard->setAnchorPoint(Vec2(0,0));
    _scoreBoard->setPosition(Vec2(0,0));
    scorePanel->addChild(_scoreBoard);
    _scorePuzzleStrategy = new SimpleScorePuzzleStrategy();
    _scoreEnemyStrategy = new SimpleScoreEnemyStrategy();

    
    this->addChild(_layout);
    
    auto stickPanel = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_stick"));
    auto stickpos =stickPanel->getPosition();
    _stick = AnalogStick::createStick("stick_inner.png", "stick_outer.png", stickpos);
    this->addChild(_stick);
    _stick->startStick();
    
    
    //initialize ui event listener
    _selectStageButton->addClickEventListener([](Ref* ref) {
        SceneMediator::getInstance()->gotoStageSelectScene();
    });
    _homeButton->addClickEventListener([](Ref* ref) {
        SceneMediator::getInstance()->gotoHomeScene();
    });
    
    _exitButton->addClickEventListener([](Ref* ref) {
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    });
    
    this->scheduleUpdate();

    return true;
}



bool GameStageScene::initData(StageDataManager* stageManager, uint32_t stageID)
{
    _stageManager = stageManager;
    _currentStageScore = stageManager->getStageScoreRecord(stageID);
    _currentStageData = _currentStageScore->getStageData();
    
    _statusManager = SceneMediator::getInstance()->getStatusDataManager();
    
    _controller = GameStageController::create(_currentStageData, _statusManager->getPlayerStatusData());
    _jewelsGrid = _controller->getJewelsGrid();
    
    _mapLayer = _controller->getMapLayer();
    UIHelper::scaleToFixFather(_mapLayer, _mapLayout);
    _mapLayer->setPosition(0, 0);
    _mapLayout->addChild(_mapLayer);
    
    //_jewelsGrid->setAnchorPoint(Vec2(400,0.5));
    _jewelsGrid->setPosition(0, 0);
    //_puzzleLayout->setContentSize(_jewelsGrid->getContentSize());
    //_jewelsGrid->setPosition(visibleSize.width/2, _jewelsGrid->getRow() * GRID_WIDTH *0);
    _puzzleLayout->addChild(_jewelsGrid);
    //this->addChild(_jewelsGrid);
    
    //TODO: may register more events here
    regEventJewelGridStatusChange();
    regEventFinishComboes();
    _jewelsGrid->startDispatchStatusChange();
    
    regEventStageClear();
    regEventEnemyDead();
    
    return true;
}


Scene* GameStageScene::createScene(StageDataManager* stageManager, uint32_t stageID)
{
    auto layer = GameStageScene::create();
    
    layer->initData(stageManager, stageID);
    
    auto scene = Scene::create();
    scene->addChild(layer);
    return scene;
}

void GameStageScene::LoadTexture()
{
    _texture_num = 0; //current number of loaded textures
    int *ptexture_num = &_texture_num;
    
    //after loading all textures
    auto addTextureCallback = [ptexture_num](Texture2D* texture)
    {
        (*ptexture_num)++;
        log("load a texture async");
    };
    
    //Async loading of the jewels
    for(int i=0; i<(int)ElementType::count;i++) {
        auto filename = ElementTypeUtils::getResourceFilename((ElementType)i);
        //Director::getInstance()->getTextureCache()->addImageAsync(filename, addTextureCallback);
        Director::getInstance()->getTextureCache()->addImage(filename);
    }
    
}

void GameStageScene::update(float delta)
{
    processController();
}

// processing functions in update()
void GameStageScene::processController()
{
    switch ((TagForDirection)(_stick->stickDirection)) {
        case TagForDirection::up:
            scheduleOnce(schedule_selector(GameStageScene::tryMovePlayerUp), DELAY_PLAYER_MOVE);
            break;
        case TagForDirection::down:
            scheduleOnce(schedule_selector(GameStageScene::tryMovePlayerDown), DELAY_PLAYER_MOVE);
            break;
        case TagForDirection::left:
            scheduleOnce(schedule_selector(GameStageScene::tryMovePlayerLeft), DELAY_PLAYER_MOVE);
            break;
        case TagForDirection::right:
            scheduleOnce(schedule_selector(GameStageScene::tryMovePlayerRight), DELAY_PLAYER_MOVE);
            break;
        default:
            break;
    }
}

// end processing functions in update()

void GameStageScene::regEventJewelGridStatusChange()
{
    auto listenner =EventListenerCustom::create(JewelsGrid::EventName_FinishCrushingMatches,
                                                CC_CALLBACK_1(GameStageScene::onJewelGridStatusChange, this));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(listenner, 100);
}

void GameStageScene::removeEventJewelGridStatusChange()
{
    getEventDispatcher()->removeCustomEventListeners(JewelsGrid::EventName_FinishCrushingMatches);
}

void GameStageScene::onJewelGridStatusChange(EventCustom* pEvent)
{
    //TODO: should stopInteraction() when JewelsGrid::onTouchBegan/End?
    stopInteraction();
    //GameStageScene* target = (GameStageScene*)pEvent->getCurrentTarget();
    CCLOG("onJewelGridStatusChange");
    
    auto data = _controller->getPuzzleStatusChangeData();
    
    /*
    auto str = Value(this->_jewelsGrid->getStatusXCombo()).asString();
    this->_textXcombo->setString(str);
    str = Value(this->_jewelsGrid->getStatusYCombo()).asString();
    this->_textYcombo->setString(str);
    */
    float duration = ELEMENT_TYPE_MATCH_COUNT_DELAY;
    
    animateComboCountChange(data, duration, CallFunc::create([&](){
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        dispatcher->dispatchCustomEvent(JewelsGrid::EventName_FinishCrushingMatches_End);
    }));
}

void GameStageScene::regEventFinishComboes()
{
    auto listenner =EventListenerCustom::create(JewelsGrid::EventName_FinishComboes,
                                                CC_CALLBACK_1(GameStageScene::onFinishComboes, this));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(listenner, 100);
}

void GameStageScene::removeEventFinishComboes()
{
    getEventDispatcher()->removeCustomEventListeners(JewelsGrid::EventName_FinishComboes);
}

void GameStageScene::onFinishComboes(cocos2d::EventCustom *pEvent)
{
    // add a "attack animation" here
    animateAttackAnimation(ATTACK_ANIMATION_DURATION, CallFunc::create([&](){
        // count down the element-x/y
        animateComboesCountDown(COMBOES_COUNT_DOWN_DURATION, CallFunc::create([&](){
            this->processScoreForPuzzle();
            
            this->hideElementXYCount();
            // handling damage/death here
            // damage logic
            this->_controller->onPuzzleFinishComboes();
            // end damage logic
            this->startInteraction();
            
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            dispatcher->dispatchCustomEvent(JewelsGrid::EventName_FinishComboes_End);
        }));
    }));
}



void GameStageScene::regEventStageClear()
{
    auto listenner =EventListenerCustom::create(GameStageController::EventNameStageClear,
                                                CC_CALLBACK_1(GameStageScene::onStageClear, this));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(listenner, 100);
}

void GameStageScene::removeEventStageCLear()
{
    getEventDispatcher()->removeCustomEventListeners(GameStageController::EventNameStageClear);
}

void GameStageScene::onStageClear(EventCustom* pEvent)
{
    //TODO: need stop any interaction here
    _stick->stopStick();
    _jewelsGrid->pauseInteraction();
    
    auto data = static_cast<StageClearData*>(pEvent->getUserData());
    auto stageClearLayer = StageClearLayer::create();
    stageClearLayer->initWithData(data);
    
    this->addChild(stageClearLayer, 10, 10);
}

void GameStageScene::tryMovePlayerUp(float delay)
{
    _controller->tryMovePlayerUp();
}

void GameStageScene::tryMovePlayerDown(float delay)
{
    _controller->tryMovePlayerDown();
}

void GameStageScene::tryMovePlayerLeft(float delay)
{
    _controller->tryMovePlayerLeft();
}

void GameStageScene::tryMovePlayerRight(float delay)
{
    _controller->tryMovePlayerRight();
}

void GameStageScene::stopInteraction()
{
    _stick->stopStick();
    _jewelsGrid->disableTounch();
}

void GameStageScene::startInteraction()
{
    _stick->startStick();
    _jewelsGrid->enableTouch();
}

/*
 * note that this is an animation and last for [duration] in the rendering time
 * not recommand to call other function after calling this function
 */
void GameStageScene::animateComboCountChange(PuzzleStatusChangeData *data, float duration, CallFunc *callback)
{
    //data should store match count of every element type for x/y
    //duration define how long for every (element) number count
    this->showElementXYCount();
    int timesChange = 10;
    //TODO: handle countChange and timesChange here
    float delay = duration / (float)timesChange;
    Vector<FiniteTimeAction*> actions;
    for (int i = 1; i<=timesChange; i++) {
        for (int type = 0; type < (int)ElementType::count; type++) {
            auto xTextName = this->getTextLabelComboCount(true, (ElementType)type);
            auto xText = dynamic_cast<ui::Text*>(this->_layout->getChildByName(xTextName));
            auto yTextName = this->getTextLabelComboCount(false, (ElementType)type);
            auto yText = dynamic_cast<ui::Text*>(this->_layout->getChildByName(yTextName));
            
            //int xFrom = 0;
            int xFrom = Value(xText->getString()).asInt();
            //int xTo = data->xCombo;
            int xTo = data->getMatchCountX((ElementType)type);
            float xStep = (xTo - xFrom) / (float)timesChange;
            //int yFrom = 0;
            int yFrom = Value(yText->getString()).asInt();
            //int yTo = data->yCombo;
            int yTo = data->getMatchCountY((ElementType)type);
            ///TODO: for debug, remove later
            //yFrom = 0;
            //yTo = 100;
            ///
            float yStep = (yTo - yFrom) / (float)timesChange;
            
            auto currentX = xTo - (int)xStep*(timesChange - i);
            auto currentY = yTo - (int)yStep*(timesChange - i);
            
            auto actionX = Sequence::create(DelayTime::create(delay), CallFunc::create([&, currentX, xText](){
                xText->setString(Value(currentX).asString());
            }), NULL);
            auto actionY = Sequence::create(DelayTime::create(delay), CallFunc::create([&, currentY, yText](){
                yText->setString(Value(currentY).asString());
            }), NULL);
            
            actions.pushBack(Spawn::create(actionX, actionY, NULL));
        }
    }
    auto sequence = Sequence::create(Sequence::create(actions),callback, NULL);
    this->runAction(sequence);
}

void GameStageScene::animateComboesCountDown(float duration, CallFunc *callback)
{
    int timesChange = 10;
    //TODO: handle countChange and timesChange here
    float delay = duration / (float)timesChange;
    Vector<FiniteTimeAction*> actions;
    for (int i = 1; i<=timesChange; i++) {
        for (int type = 0; type < (int)ElementType::count; type++) {
            auto xTextName = this->getTextLabelComboCount(true, (ElementType)type);
            auto xText = dynamic_cast<ui::Text*>(this->_layout->getChildByName(xTextName));
            auto yTextName = this->getTextLabelComboCount(false, (ElementType)type);
            auto yText = dynamic_cast<ui::Text*>(this->_layout->getChildByName(yTextName));
            
            int xFrom = Value(xText->getString()).asInt();
            int xTo = 0;
            float xStep = (xTo - xFrom) / (float)timesChange;
            int yFrom = Value(yText->getString()).asInt();
            int yTo = 0;
            float yStep = (yTo - yFrom) / (float)timesChange;
            
            auto currentX = xTo - (int)xStep*(timesChange - i);
            auto currentY = yTo - (int)yStep*(timesChange - i);
            
            auto actionX = Sequence::create(DelayTime::create(delay), CallFunc::create([&, currentX, xText](){
                xText->setString(Value(currentX).asString());
            }), NULL);
            auto actionY = Sequence::create(DelayTime::create(delay), CallFunc::create([&, currentY, yText](){
                yText->setString(Value(currentY).asString());
            }), NULL);
            
            actions.pushBack(Spawn::create(actionX, actionY, NULL));
        }
    }
    auto sequence = Sequence::create(Sequence::create(actions),callback, NULL);
    this->runAction(sequence);
}

void GameStageScene::animateAttackAnimation(float duration, CallFunc *callback)
{
    Vector<FiniteTimeAction*> actions;
    
    auto actionEmpty = Sequence::create(DelayTime::create(0), CallFunc::create([&](){
    }), NULL);
    actions.pushBack(actionEmpty);
    
    if (_controller->canAttackEnemy()) {
        _puzzleEffectLayout->setOpacity(0);
        _puzzleEffectLayout->setVisible(true);
        
        
        auto actionShow = Sequence::create(DelayTime::create(0), CallFunc::create([&,duration](){
            this->_puzzleEffectLayout->runAction(FadeTo::create(duration, 128));
            
        }), NULL);
        auto actionHide = Sequence::create(DelayTime::create(duration), CallFunc::create([&, duration](){
            this->_puzzleEffectLayout->runAction(FadeOut::create(duration));
        }), NULL);
        auto actionNotVisable = Sequence::create(DelayTime::create(duration), CallFunc::create([&](){
            this->_puzzleEffectLayout->setVisible(false);
        }), NULL);
        
        
        actions.pushBack(actionShow);
        actions.pushBack(actionHide);
        actions.pushBack(actionNotVisable);
    }
    
    auto sequence = Sequence::create(Sequence::create(actions),callback, NULL);
    this->runAction(sequence);
}

std::string GameStageScene::getTextLabelComboCount(bool isX, ElementType type)
{
    std::string xOrY = (isX)?("Text_xCombo"):("Text_yCombo");
    auto ret = xOrY + ElementTypeUtils::toString(type);
    return ret;
}

void GameStageScene::hideElementXYCount()
{
    for (int type = 0; type < (int)ElementType::count; type++) {
        auto xTextName = this->getTextLabelComboCount(true, (ElementType)type);
        auto xText = dynamic_cast<ui::Text*>(this->_layout->getChildByName(xTextName));
        xText->setVisible(false);
        auto yTextName = this->getTextLabelComboCount(false, (ElementType)type);
        auto yText = dynamic_cast<ui::Text*>(this->_layout->getChildByName(yTextName));
        yText->setVisible(false);
    }
}

void GameStageScene::showElementXYCount()
{
    for (int type = 0; type < (int)ElementType::count; type++) {
        auto xTextName = this->getTextLabelComboCount(true, (ElementType)type);
        auto xText = dynamic_cast<ui::Text*>(this->_layout->getChildByName(xTextName));
        xText->setVisible(true);
        auto yTextName = this->getTextLabelComboCount(false, (ElementType)type);
        auto yText = dynamic_cast<ui::Text*>(this->_layout->getChildByName(yTextName));
        yText->setVisible(true);
    }
}

void GameStageScene::processScoreForPuzzle()
{
    auto data = _controller->getPuzzleStatusChangeData();
    auto scoreToAdd = _scorePuzzleStrategy->getScoreToAdd(data);
    auto score = _scoreBoard->getScore();
    auto result = score+scoreToAdd;
    _scoreBoard->setScore(result);
    _controller->setScore(result);
}


void GameStageScene::regEventEnemyDead()
{
    auto listenner =EventListenerCustom::create(GameStageController::EventNameEnemyDead,
                                                CC_CALLBACK_1(GameStageScene::onEnemyDead, this));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(listenner, 100);
}

void GameStageScene::removeEventEnemyDead()
{
    getEventDispatcher()->removeCustomEventListeners(GameStageController::EventNameEnemyDead);
}

void GameStageScene::onEnemyDead(EventCustom* pEvent)
{
    auto enemy = static_cast<MapItemEnemy*>(pEvent->getUserData());
    auto scoreToAdd = _scoreEnemyStrategy->getScoreToAdd(enemy);
    auto score = _scoreBoard->getScore();
    auto result = score+scoreToAdd;
    _scoreBoard->setScore(result);
    _controller->setScore(result);
}
