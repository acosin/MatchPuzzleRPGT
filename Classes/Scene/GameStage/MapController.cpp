//
//  MapController.cpp
//  MatchPuzzleRPGT
//
//

#include "MapController.h"

#include "SimpleMapStrategyOnPuzzleStatusChange.h"
#include "SimpleMapStrategyWithUnitsOnPuzzleStatusChange.h"

MapController::MapController(StageData *stageData)
{
    _IDpool_mapItem = new IDPool();
    initMap(stageData);
    
    //_strategyOnPuzzle = new SimpleMapStrategyOnPuzzleStatusChange();
    _strategyOnPuzzle = new SimpleMapStrategyWithUnitsOnPuzzleStatusChange();
}

MapController::~MapController()
{
    CC_SAFE_DELETE(_IDpool_mapItem);
    CC_SAFE_DELETE(_mapLayer);
}

bool MapController::initMap(StageData *stageData)
{
    if (stageData == nullptr) {
        return false;
    }
    
    _stageData = stageData;
    
    createMapLayerFromData();
    CC_ASSERT(_mapLayer != nullptr);
    
    createEnemies();
    //createEnemiesDebug();
    
    return true;
}

MapLayer* MapController::getMapLayer()
{
    return _mapLayer;
}


int MapController::getPlayerX()
{
    return _playerItem->getX();
}

int MapController::getPlayerY()
{
    return _playerItem->getY();
}


void MapController::movePlayerTo(int x, int y)
{
    _lastPlayerX = _playerItem->getX();
    _lastPlayerY = _playerItem->getY();
    
    _playerItem->setXY(x, y);
    // TODO: may update rendering
    /*
    auto sprite = _playerItem->getSprite();
    _mapLayer->moveSpriteOnMap(sprite, x, y);
     */
    auto node = _playerItem->getNode();
    _mapLayer->moveNodeOnMap(node, x, y);
    
    auto goal = checkGoal();
}

bool MapController::isValidTilePos(int x, int y)
{
    return (x>=0 && y>=0 && x< _stageData->_mapWidth && y < _stageData->_mapHeight);
}

bool MapController::isWalkableTilePos(int x, int y)
{
    return (findMapItems(x,y).size() == 0);
}

bool MapController::tryMovePlayerTo(int x, int y)
{
    CC_ASSERT(_IDpool_mapItem != nullptr);
    if (!isValidTilePos(x, y)) {
        //CCLOG("(%d,%d) out of map", x,y);
        return false;
    }
    
    if (!isWalkableTilePos(x, y)) {
        CCLOG("already exist item in (%d,%d)", x,y);
        return false;
    }
    
    movePlayerTo(x, y);
    return true;
}


bool MapController::tryMovePlayerUp()
{
    auto x = _playerItem->getX();
    auto y = _playerItem->getY();
    return tryMovePlayerTo(x, y-1);
}
bool MapController::tryMovePlayerDown()
{
    auto x = _playerItem->getX();
    auto y = _playerItem->getY();
    return tryMovePlayerTo(x, y+1);
}
bool MapController::tryMovePlayerLeft()
{
    auto x = _playerItem->getX();
    auto y = _playerItem->getY();
    return tryMovePlayerTo(x-1, y);
}
bool MapController::tryMovePlayerRight()
{
    auto x = _playerItem->getX();
    auto y = _playerItem->getY();
    return tryMovePlayerTo(x+1, y);
}


MapLayer* MapController::createMapLayerFromData()
{
    CC_ASSERT(_stageData != nullptr);
    auto mapFilename = StageData::getMapTMXFilename(0); //TODO: get from _stageData
    //auto mapFilename = StageData::getMapTMXFilename(_stageData->_mapID); //TODO: get from _stageData
    auto playerFilename = "Player_on_map.png"; //TODO: get from _playerItem // remove
    
    //_mapLayer = MapLayer::create(mapFilename, playerFilename);
    _mapLayer = MapLayer::create(mapFilename);
    //createPlayerItem(2, 3, playerFilename);
    //TODO: should get this from StageData
    createPlayerItem(_stageData->_playerInitialX, _stageData->_playerInitialY, playerFilename);
    //createPlayerItem(2, 2, playerFilename);
    
    return _mapLayer;
}


bool MapController::moveMapItemTo(uint32_t id, int x, int y)
{
    CC_ASSERT(_IDpool_mapItem != nullptr);
    if (!_IDpool_mapItem->exist(id)) {
        return false;
    }
    
    auto item = _mapItems[id];
    //TODO: may need animation
    item->setXY(x, y);
    
    //auto sprite = item->getSprite();
    //_mapLayer->moveSpriteOnMap(sprite, x, y);
    auto node = item->getNode();
    _mapLayer->moveNodeOnMap(node, x, y);
    
    return true;
}

//
bool MapController::tryMoveMapItemTo(uint32_t id, int x, int y)
{
    CC_ASSERT(_IDpool_mapItem != nullptr);
    if (findMapItems(x, y).size() != 0) {
        CCLOG("already exist item in (%d,%d)", x,y);
        return false;
    }
    return moveMapItemTo(id, x, y);
}

std::vector<uint32_t> MapController::findMapItems(int x, int y)
{
    std::vector<uint32_t> itemIDs;
    // TODO: may need to consider the traversal speed
    for (auto item : _mapItems) {
        if (item.second->getX() == x && item.second->getY() == y) {
            itemIDs.push_back(item.second->getID());
        }
    }
    return itemIDs;
}

bool MapController::removeMapItem(uint32_t id)
{
    bool ret = false;
    
    if (_IDpool_mapItem->exist(id)) {
        _mapItems.erase(id);
        _IDpool_mapItem->removeID(id);
        ret = true;
    }
    
    return ret;
}


bool MapController::removeMapItem(IMapItem* pItem)
{
    if (pItem == nullptr)
        return false;
    return removeMapItem(pItem->getID());
}



bool MapController::createPlayerItem(int x, int y, const std::string &imagePath)
{
    CC_ASSERT(_mapLayer != nullptr);
    
    _playerItem = new MapItemPlayer(x, y, imagePath);
    auto id = _IDpool_mapItem->generateID();
    _playerItem->setID(id);
    auto sprite = Sprite::create(imagePath);
    sprite->setAnchorPoint(Vec2(0,0));
    //change this to pixel coordinate
    sprite->setPosition(_mapLayer->convertToPixelPos(Vec2(x,y)));
    //_playerItem->setSprite(sprite);
    _playerItem->setNode(sprite);
    _mapLayer->initPlayer(sprite);
    
    return true;
}


uint32_t MapController::createEnemyItem(int x, int y, const std::string &imagePath)
{
    uint32_t id = 0;
    
    if (_mapLayer == nullptr) {
        return 0;
    }
    
    auto enemy = new MapItemEnemy(x,y,imagePath);
    id = _IDpool_mapItem->generateID();
    enemy->setID(id);
    //TODO: set data later
    //enemy->setStatusData(EnemyStatusData *statusData);
    
    //auto node = Sprite::create(imagePath);
    auto node = EnemyNode::createNode(imagePath);
    
    node->setAnchorPoint(Vec2(0,0));
    //change this to pixel coordinate
    auto pos = _mapLayer->convertToPixelPos(Vec2(x,y));
    node->setPosition(pos);
    //node->setPosition(_mapLayer->convertToPixelPos(Vec2(0,0)));
    enemy->setNode(node);
    _mapItems[id] = enemy;
    //TODO: scale enemy item here, may remove later (image should be ideal size)
    _mapLayer->scaleAsTileSize(node);
    _mapLayer->addChild(node);
    
    return id;
}

uint32_t MapController::createEnemyItem(int x, int y, EnemyStatusData *data)
{
    uint32_t id = 0;
    
    if (_mapLayer == nullptr) {
        return 0;
    }
    
    auto imagePath = data->getSpriteImagePath();
    
    auto enemy = new MapItemEnemy(x,y,imagePath);
    id = _IDpool_mapItem->generateID();
    enemy->setID(id);
    enemy->setStatusData(data);
    
    //auto node = Sprite::create(imagePath);
    auto node = EnemyNode::createNode(imagePath);
    
    node->setAnchorPoint(Vec2(0,0));
    //change this to pixel coordinate
    auto pos = _mapLayer->convertToPixelPos(Vec2(x,y));
    node->setPosition(pos);
    //node->setPosition(_mapLayer->convertToPixelPos(Vec2(0,0)));
    enemy->setNode(node);
    _mapItems[id] = enemy;
    //TODO: scale enemy item here, may remove later (image should be ideal size)
    _mapLayer->scaleAsTileSize(node);
    _mapLayer->addChild(node);
    
    return id;
}

// -- public for game logic--
void MapController::onPuzzleStatusChange(PuzzleStatusChangeData *data)
{
    _strategyOnPuzzle->exec(this, data);
}


std::map<uint32_t, MapItemEnemy*>MapController::getEnemyAround(int x, int y)
{
    std::map<uint32_t, MapItemEnemy*> ret;
    for (auto item : _mapItems) {
        if (item.second->getType() == MapItemType::Enemy) {
            auto enemy = item.second;
            if (abs(enemy->getX() - x) + abs(enemy->getY()-y) == 1) {
                ret.insert(item);
            }
        }
    }
    return ret;
}

bool MapController::isGoalPos(int x, int y)
{
    return _mapLayer->isGoalPos(x, y);
}

bool MapController::checkGoal()
{
    if (isGoalPos(getPlayerX(), getPlayerY())) {
        return true;
    }
    return false;
}

int MapController::getEnemyCount()
{
    int ret = 0;
    for (auto item : _mapItems) {
        if (item.second->getType() == MapItemType::Enemy) {
            ret++;
        }
    }
    return ret;
}

void MapController::dispatchEnemyDeadEvent(MapItemEnemy *enemy)
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(GameStageController::EventNameEnemyDead, enemy);
}

int MapController::getUnitDamage(ElementType type)
{
    auto strategy = dynamic_cast<SimpleMapStrategyWithUnitsOnPuzzleStatusChange*>(_strategyOnPuzzle);
    return strategy->getUnitElementDamage(type);
}

// -- private --


//NOTE: not used
/*
std::map<uint32_t, MapItemEnemy*>::iterator MapController::findMapItem(uint32_t id)
{
    std::map<uint32_t, MapItemEnemy*>::iterator it;
    for (it = _mapItems.begin(); it != _mapItems.end(); it++) {
        if ((*it).second->getID() == id) {
            return it;
        }
    }
    return it;
}

std::map<uint32_t, MapItemEnemy*>::iterator MapController::findMapItem(IMapItem* ptr)
{
    return find(_mapItems.begin(), _mapItems.end(), ptr);
}
*/


// create enemies from
void MapController::createEnemies()
{
    std::string enemyDataFile = "data/EnemyStatusData.csv";
    _enemyData = EnemyStatusData::loadEnemyDataFromCSV(enemyDataFile);
    
    auto enemyGroup = _mapLayer->_tileMap->getObjectGroup("Enemies");
    auto enemies = enemyGroup->getObjects();
    for (auto enemy : enemies) {
        auto properties = enemy.asValueMap();
        auto mapx = properties["MapX"].asInt();
        auto mapy = properties["MapY"].asInt();
        auto enemyid = (uint32_t)(properties["EnemyID"].asInt());
        createEnemyItem(mapx, mapy, _enemyData[enemyid]);
    }
}

void MapController::createEnemiesDebug()
{
    //TODO: should create every enemy from csv/json data later
    EnemyStatusData* data;
    
    data = new EnemyStatusData(0,    // enemyID,
                               "element_0.png",   //iconPath,
                               //std::string imagePath,
                               "EnemyName_0",     //enemyName,
                               ElementType::RED,  //type,
                               0,    //level,
                               100,   //hp,
                               1     //atk
                               );
    //createEnemyItem(1,2,"element_0.png");
    createEnemyItem(1,2,data);
    
    data = new EnemyStatusData(0,    // enemyID,
                               "element_0.png",   //iconPath,
                               //std::string imagePath,
                               "EnemyName_0",     //enemyName,
                               ElementType::RED,  //type,
                               0,    //level,
                               100,   //hp,
                               1     //atk
                               );
    //createEnemyItem(2,1,"element_0.png");
    createEnemyItem(2,1,data);
    
    data = new EnemyStatusData(1,    // enemyID,
                               "element_1.png",   //iconPath,
                               //std::string imagePath,
                               "EnemyName_1",     //enemyName,
                               ElementType::BLUE,  //type,
                               0,    //level,
                               2,   //hp,
                               1     //atk
                               );
    //createEnemyItem(1,0,"element_1.png");
    createEnemyItem(1,0,data);
    
    data = new EnemyStatusData(1,    // enemyID,
                               "element_1.png",   //iconPath,
                               //std::string imagePath,
                               "EnemyName_1",     //enemyName,
                               ElementType::BLUE,  //type,
                               0,    //level,
                               10,   //hp,
                               1     //atk
                               );
    //createEnemyItem(3,0,"element_1.png");
    createEnemyItem(3,0,data);
    
    data = new EnemyStatusData(0,    // enemyID,
                               "element_0.png",   //iconPath,
                               //std::string imagePath,
                               "EnemyName_0",     //enemyName,
                               ElementType::RED,  //type,
                               0,    //level,
                               10,   //hp,
                               1     //atk
                               );
    //createEnemyItem(4,2,"element_0.png");
    createEnemyItem(4,2,data);
}

MapController::ShortestPathStep::ShortestPathStep() :
_position(Point::ZERO),
_gScore(0),
_hScore(0),
_parent(nullptr)
{
    
}

MapController::ShortestPathStep::~ShortestPathStep()
{
    
}

MapController::ShortestPathStep* MapController::ShortestPathStep::createWithPosition(const Point &pos)
{
    ShortestPathStep *pRet = new ShortestPathStep();
    if (pRet && pRet->initWithPosition(pos)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool MapController::ShortestPathStep::initWithPosition(const Point &pos)
{
    bool bRet = false;
    //TODO
    do {
        this->setPosition(pos);
        bRet = true;
    } while (0);
    return bRet;
}

int MapController::ShortestPathStep::getFScore() const
{
    return this->getGScore() + this->getHScore();
}

bool MapController::ShortestPathStep::isEqual(const ShortestPathStep *other) const
{
    return this->getPosition() == other->getPosition();
}

std::string MapController::ShortestPathStep::getDescription() const
{
    return StringUtils::format("pos=[%.0f;%.0f]  g=%d  h=%d  f=%d",
                               this->getPosition().x, this->getPosition().y,
                               this->getGScore(), this->getHScore(), this->getFScore());
}


void MapController::insertInOpenSteps(ShortestPathStep *step)
{
    int stepFscore = step->getFScore();
    ssize_t count = _mapitemOpenSteps.size();
    ssize_t i = 0;
    for (; i < count; i++) {
        if (stepFscore <= _mapitemOpenSteps.at(i)->getFScore()) {
            break;
        }
    }
    _mapitemOpenSteps.insert(i, step);
}

int MapController::computeHScoreFromPosToPos(const Point &fromPos, const Point &toPos)
{
    return (int)(abs(toPos.x - fromPos.x) + abs(toPos.y - fromPos.y));
}

int MapController::costToMoveFromStepToAdjacentStep(const ShortestPathStep *fromStep, const ShortestPathStep *toStep)
{
    return 1;
}

PointArray* MapController::walkableAdjacentTilesPosForTilePos(const Point &tilePos)
{
    PointArray *tmp = PointArray::create(4);
    // up
    Point p(tilePos.x,tilePos.y-1);
    if (isValidTilePos(p.x, p.y) && isWalkableTilePos(p.x, p.y)) {
        tmp->addControlPoint(p);
    }
    // left
    p.set(tilePos.x-1, tilePos.y);
    if (isValidTilePos(p.x, p.y) && isWalkableTilePos(p.x, p.y)) {
        tmp->addControlPoint(p);
    }
    // down
    p.set(tilePos.x, tilePos.y+1);
    if (isValidTilePos(p.x, p.y) && isWalkableTilePos(p.x, p.y)) {
        tmp->addControlPoint(p);
    }
    // right
    p.set(tilePos.x+1, tilePos.y);
    if (isValidTilePos(p.x, p.y) && isWalkableTilePos(p.x, p.y)) {
        tmp->addControlPoint(p);
    }
    return tmp;
}

ssize_t MapController::getStepIndex(const Vector<ShortestPathStep*> &steps, const ShortestPathStep *step)
{
    for (ssize_t i = 0; i < steps.size(); i++) {
        if (steps.at(i)->isEqual(step)) {
            return i;
        }
    }
    return -1;
}

void MapController::constructPath(MapController::ShortestPathStep *step)
{
    _shortestPath.clear();
    
    do {
        if (step->getParent()) {
            _shortestPath.insert(0, step);
        }
        step = step->getParent();
    } while (step);
    
    for (auto s : _shortestPath) {
        CCLOG("%s", s->getDescription().c_str());
    }
}

void MapController::constructPathAndStartMoveFromStep(MapController::ShortestPathStep *step)
{
    _shortestPath.clear();
    
    do {
        if (step->getParent()) {
            _shortestPath.insert(0, step);
        }
        step = step->getParent();
    } while (step);
    
    for (auto s : _shortestPath) {
        CCLOG("%s", s->getDescription().c_str());
    }
    
    animateMovebyPopAlongPath();
}

void MapController::animateMovebyPopAlongPath()
{
    _mapLayer->disableTouch();
    if (_shortestPath.size() == 0) {
        _mapLayer->enableTouch();
        return;
    }
    
    float durationMoveOnce = 0.3;
    
    auto s = _shortestPath.at(0);
    auto x = s->getPosition().x;
    auto y = s->getPosition().y;
    auto moveAction = Sequence::create(DelayTime::create(durationMoveOnce), CallFunc::create([&, x, y](){
        this->movePlayerTo(x, y);
    }), NULL);
    auto moveCallback = CallFunc::create(CC_CALLBACK_0(MapController::animateMovebyPopAlongPath, this));
    _shortestPath.erase(0);
    _mapLayer->runAction(Sequence::create(moveAction,moveCallback, NULL));
}

bool MapController::tryMovePlayerByAstar(const Point &target)
{
    bool pathFound = false;
    
    _mapitemOpenSteps.clear();
    _mapitemClosedSteps.clear();
    
    Point playerFrom = Point(getPlayerX(), getPlayerY());
    insertInOpenSteps(ShortestPathStep::createWithPosition(playerFrom));
    
    do {
        // get min F value
        // the first is min because it is an ordered list
        auto currentStep = _mapitemOpenSteps.at(0);
        // add current step to the closed list
        _mapitemClosedSteps.pushBack(currentStep);
        // and then remove it from the open list
        _mapitemOpenSteps.erase(0);

        
        // if current step is target, then finish
        if (currentStep->getPosition() == target) {
            pathFound = true;
            //constructPathAndStartMoveFromStep(currentStep);
            constructPath(currentStep);
            /*
            auto tmpStep = currentStep;
            CCLOG("path found: ");
            do {
                CCLOG("%s", tmpStep->getDescription().c_str());
                tmpStep = tmpStep->getParent(); //backward
            } while (tmpStep); // until cannot backward
             */
            _mapitemOpenSteps.clear();
            _mapitemClosedSteps.clear();
            break;
        }
        
        // get adjacent of current step
        auto adjSteps = walkableAdjacentTilesPosForTilePos(currentStep->getPosition());
        for (ssize_t i = 0; i < adjSteps->count(); i++) {
            auto step = ShortestPathStep::createWithPosition(adjSteps->getControlPointAtIndex(i));
            // check if this step already in closed list
            if (getStepIndex(_mapitemClosedSteps, step) != -1) {
                continue;
            }
            
            // compute the cost from current step to this step
            auto movecost = costToMoveFromStepToAdjacentStep(currentStep, step);
            // check if this step in the open list
            auto index = getStepIndex(_mapitemOpenSteps, step);
            // not in open list, add it
            if (index == -1) {
                // set current step as parent
                step->setParent(currentStep);
                // G value = G value of current step + movecost
                step->setGScore(currentStep->getGScore() + movecost);
                // H value
                step->setHScore(computeHScoreFromPosToPos(step->getPosition(), target));
                // insert by order
                insertInOpenSteps(step);
            } else {
                // get existing step, it has been computed
                step = _mapitemOpenSteps.at(index);
                // check whether G value < ...
                if ((currentStep->getGScore() + movecost) < step->getGScore()) {
                    // set G value as the smaller one
                    step->setGScore(currentStep->getGScore() + movecost);
                    // F value would change according to the change of G value
                    // to keep the open list ordered, we need to remove this step and then insert by order
                    // before remove, retain the ref
                    step->retain();
                    // now can remove from the list while guarantee no memory release
                    _mapitemOpenSteps.erase(index);
                    // insert by order again
                    insertInOpenSteps(step);
                    // now we can release it, because the open list holds it
                    step->release();
                }
            }
        }
        
    } while (_mapitemOpenSteps.size() > 0);
    
    if (!pathFound) {
        CCLOG("cannot found a path");
    }
    return pathFound;
}

Vector<MapController::ShortestPathStep*>& MapController::getShortestPath()
{
    return _shortestPath;
}

void MapController::popFirstStepOfPath()
{
    if (_shortestPath.size() != 0) {
        _shortestPath.erase(0);
    }
}
