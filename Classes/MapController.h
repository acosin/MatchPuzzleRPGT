//
//  MapController.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include "cocos2d.h"
#include <map>
#include <vector>

#include "StageData.h"
#include "MapItemEnemy.h"
#include "MapItemPlayer.h"
#include "MapLayer.h"

#include "IDPool.h"

#include "EnemyNode.h"
#include "PuzzleStatusChangeData.hpp"
#include "IMapStrategyOnPuzzleStatusChange.h"

//cross
#include "GameStageController.h"

USING_NS_CC;

class GameStageController;

class IMapStrategyOnPuzzleStatusChange;

class MapController
{
private:
    StageData* _stageData = nullptr;
    MapLayer* _mapLayer = nullptr;
    
    IDPool* _IDpool_mapItem = nullptr;
    MapItemPlayer* _playerItem = nullptr;
    int _lastPlayerX, _lastPlayerY;
    std::map<uint32_t, EnemyStatusData*> _enemyData;
    std::map<uint32_t, MapItemEnemy*> _mapItems;
    
    IMapStrategyOnPuzzleStatusChange *_strategyOnPuzzle;
public:
    MapController(StageData *stageData);
    ~MapController();
    
    bool initMap(StageData* stageData);
    MapLayer* getMapLayer();
    
    MapLayer* createMapLayerFromData();
    
    int getPlayerX();
    int getPlayerY();
    bool isValidTilePos(int x, int y);
    bool isWalkableTilePos(int x, int y);
    void movePlayerTo(int x, int y);
    bool tryMovePlayerTo(int x, int y);
    bool tryMovePlayerUp();
    bool tryMovePlayerDown();
    bool tryMovePlayerLeft();
    bool tryMovePlayerRight();
    bool createPlayerItem(int x, int y, const std::string &imagePath);
    
    bool moveMapItemTo(uint32_t id, int x, int y);
    bool tryMoveMapItemTo(uint32_t id, int x, int y);
    std::vector<uint32_t> findMapItems(int x, int y);
    bool removeMapItem(uint32_t id);
    bool removeMapItem(IMapItem* pItem);
    
    //NOTE: return 0 if cannot create
    uint32_t createEnemyItem(int x, int y, const std::string &imagePath);
    uint32_t createEnemyItem(int x, int y, EnemyStatusData *data);

    //for game logic
public:
    void onPuzzleStatusChange(PuzzleStatusChangeData *data);
    std::map<uint32_t, MapItemEnemy*> getEnemyAround(int x, int y);
    
    bool isGoalPos(int x, int y);
    bool checkGoal();
    int getEnemyCount();
    void dispatchEnemyDeadEvent(MapItemEnemy* enemy);
    
    int getUnitDamage(ElementType type);
private:
    /*
    std::vector<IMapItem*>::iterator findMapItem(uint32_t id);
    std::vector<IMapItem*>::iterator findMapItem(IMapItem* ptr);
    */
    void createEnemies();
    void createEnemiesDebug();
    
// -- for A* path searching --
protected:
    class ShortestPathStep : public Ref
    {
    public:
        ShortestPathStep();
        ~ShortestPathStep();
        static ShortestPathStep *createWithPosition(const Point &pos);
        bool initWithPosition(const Point &pos);
        int getFScore() const;
        bool isEqual(const ShortestPathStep *other) const;
        std::string getDescription() const;
        CC_SYNTHESIZE(Point, _position, Position);
        CC_SYNTHESIZE(int, _gScore, GScore);
        CC_SYNTHESIZE(int, _hScore, HScore);
        CC_SYNTHESIZE(ShortestPathStep*, _parent, Parent);
        
    };
    
    void insertInOpenSteps(ShortestPathStep *step);
    int computeHScoreFromPosToPos(const Point &fromPos, const Point &toPos);
    int costToMoveFromStepToAdjacentStep(const ShortestPathStep *fromStep, const ShortestPathStep *toStep);
    PointArray* walkableAdjacentTilesPosForTilePos(const Point &tilePos);
    ssize_t getStepIndex(const Vector<ShortestPathStep*> &steps, const ShortestPathStep *step);
    
    void constructPathAndStartMoveFromStep(ShortestPathStep *step);
    void animateMovebyPopAlongPath();
protected:
    Vector<ShortestPathStep*> _mapitemOpenSteps;
    Vector<ShortestPathStep*> _mapitemClosedSteps;
    Vector<ShortestPathStep*> _shortestPath;
public:
    bool tryMovePlayerByAstar(const Point &target);
};
