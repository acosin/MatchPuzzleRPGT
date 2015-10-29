//
//  GameStageScene.cpp
//  MatchPuzzleRPGT
//
//

#include "GameStageScene.h"

const string JewelsGrid::eventNameStatusChange = "event_JewelGridStatusChange";

GameStageScene::GameStageScene():
_layout(nullptr),
_puzzleLayout(nullptr),
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
_mapLayer(nullptr)
{
    
}

GameStageScene::~GameStageScene()
{
    removeEventJewelGridStatusChange();
    removeEventStageCLear();
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
    _mapLayout = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_map"));
    
    _textXcombo = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_xCombo"));
    _textYcombo = dynamic_cast<ui::Text*>(_layout->getChildByName("Text_yCombo"));
    
    _homeButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_backHome"));
    _exitButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_exit"));
    _selectStageButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_selectStage"));
    
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
    
    _controller = GameStageController::create(_currentStageData);
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
    _jewelsGrid->startDispatchStatusChange();
    
    regEventStageClear();
    
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
    //TODO: may change to use Action or animation here
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

void GameStageScene::regEventJewelGridStatusChange()
{
    auto listenner =EventListenerCustom::create(JewelsGrid::eventNameStatusChange,
                                                CC_CALLBACK_1(GameStageScene::onJewelGridStatusChange, this));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(listenner, 100);
}

void GameStageScene::removeEventJewelGridStatusChange()
{
    getEventDispatcher()->removeCustomEventListeners(JewelsGrid::eventNameStatusChange);
}

void GameStageScene::onJewelGridStatusChange(EventCustom* pEvent)
{
    //TODO: should stopInteraction() when JewelsGrid::onTouchBegan/End?
    stopInteraction();
    //GameStageScene* target = (GameStageScene*)pEvent->getCurrentTarget();
    CCLOG("onJewelGridStatusChange");
    
    /*
    auto str = Value(this->_jewelsGrid->getStatusXCombo()).asString();
    this->_textXcombo->setString(str);
    str = Value(this->_jewelsGrid->getStatusYCombo()).asString();
    this->_textYcombo->setString(str);
    */
    float duration = 0.5;
    animateComboCountChange(_controller->getPuzzleStatusChangeData(), duration);
    
    //TODO: may need async here
    //_stick->stopStick();
    
    _controller->onPuzzleStatusChange();
    //(animation)
    //_stick->startStick();
    startInteraction();
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
    
    int timesChange = 10;
    int xFrom = 0;
    int xTo = data->xCombo;
    float xStep = (xTo - xFrom) / (float)timesChange;
    int yFrom = 0;
    int yTo = data->yCombo;
    float yStep = (xTo - xFrom) / (float)timesChange;
    //TODO: handle countChange and timesChange here
    float delay = duration / (float)timesChange;
    Vector<FiniteTimeAction*> actions;
    for (int i = 1; i<=timesChange; i++) {
        for (int type = 0; type < (int)ElementType::count; type++) {
            auto currentX = xTo - (int)xStep*(timesChange - i);
            auto currentY = yTo - (int)yStep*(timesChange - i);
            
            auto actionX = Sequence::create(DelayTime::create(delay), CallFunc::create([&, currentX, type](){
                auto xTextName = this->getTextLabelComboCount(true, (ElementType)type);
                //TODO
                xTextName = "Text_xCombo";
                auto xText = dynamic_cast<ui::Text*>(this->_layout->getChildByName(xTextName));
                xText->setString(Value(currentX).asString());
            }), NULL);
            auto actionY = Sequence::create(DelayTime::create(delay), CallFunc::create([&, currentY, type](){
                auto yTextName = this->getTextLabelComboCount(false, (ElementType)type);
                //TODO
                yTextName = "Text_yCombo";
                auto yText = dynamic_cast<ui::Text*>(this->_layout->getChildByName(yTextName));
                yText->setString(Value(currentY).asString());
            }), NULL);
            
            actions.pushBack(Spawn::create(actionX, actionY, NULL));
        }
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
