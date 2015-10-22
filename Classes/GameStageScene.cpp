//
//  GameStageScene.cpp
//  MatchPuzzleRPGT
//
//

#include "GameStageScene.h"

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
    
}

bool GameStageScene::init()
{
    if (Layer::init()==false) {
        return false;
    }
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    _layout = CSLoader::createNode("ui/GameStageScene.csb");
    _layout->setName("LAYOUT");
    
    // TODO: may create only once in SceneMediator?
    //_background = SceneMediator::getInstance()->getMainBackground();
    _background = MainBackground::create();
    _layout->getChildByName("ImageView_background")->addChild(_background);
    
    _puzzleLayout = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_puzzle"));
    _mapLayout = dynamic_cast<ui::Layout*>(_layout->getChildByName("Panel_map"));
    
    _homeButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_backHome"));
    _exitButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_exit"));
    _selectStageButton = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_selectStage"));
    
    this->addChild(_layout);
    
    
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

    return true;
}



bool GameStageScene::initData(StageDataManager* stageManager, uint32_t stageID)
{
    _stageManager = stageManager;
    _currentStageScore = stageManager->getStageScoreRecord(stageID);
    _currentStageData = _currentStageScore->getStageData();
    
    //NOTE: should load texture before creating Jewel class!
    LoadTexture();
    
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

void GameStageScene::movePlayerTo(int x, int y)
{
    
}

