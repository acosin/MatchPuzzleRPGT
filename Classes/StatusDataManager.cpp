//
//  StatusDataManager.cpp
//  MatchPuzzleRPGT
//
//

#include "StatusDataManager.h"


StatusDataManager::StatusDataManager():
_playerData(nullptr)
{
    this->setCascadeOpacityEnabled(true);
}

StatusDataManager::~StatusDataManager()
{
    this->removeAllChildren();
}

StatusDataManager* StatusDataManager::create()
{
    auto m = new StatusDataManager();
    
    if (m && m->initWithData()) {
        m->autorelease();
        return m;
    }
    
    CC_SAFE_DELETE(m);
    
    return nullptr;
}

bool StatusDataManager::initWithData()
{
    if (Layer::init()==false)
        return false;
    
    // TODO: init playerData, UnitRecords here
    //
    return true;
}
