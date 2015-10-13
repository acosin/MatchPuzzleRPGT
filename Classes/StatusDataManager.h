//
//  StatusDataManager.h
//  MatchPuzzleRPGT
//
//

#ifndef __MatchPuzzleRPGT__StatusDataManager__
#define __MatchPuzzleRPGT__StatusDataManager__

#include "cocos2d.h"

#include "UnitOfPlayerRecord.h"
#include "PlayerStatusData.h"

USING_NS_CC;

class StatusDataManager : public Layer
{
protected:
    PlayerStatusData* _playerData;
    std::vector<UnitOfPlayerRecord*> _unitRecords;
    
public:
    StatusDataManager();
    virtual ~StatusDataManager();
    
    static StatusDataManager* create();
    
    virtual bool initWithoutData(); // TODO: may remove later
    virtual bool initWithData(PlayerStatusData* playerData, std::vector<UnitOfPlayerRecord*> &unitRecords);
    virtual bool initFromLocalData();
    
    // TODO: for debug, remove later
public:
    bool initWithDebugData();
};

#endif /* defined(__MatchPuzzleRPGT__StatusDataManager__) */