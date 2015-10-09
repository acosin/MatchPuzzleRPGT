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
using namespace std;

class StatusDataManager : public Layer
{
protected:
    PlayerStatusData* _playerData;
    vector<UnitOfPlayerRecord*> _unitRecords;
    
public:
    StatusDataManager();
    virtual ~StatusDataManager();
    
    static StatusDataManager* create();
    
    virtual bool initWithData();
};

#endif /* defined(__MatchPuzzleRPGT__StatusDataManager__) */