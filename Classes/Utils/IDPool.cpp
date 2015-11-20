//
//  IDPool.cpp
//  MatchPuzzleRPGT
//
//

#include "IDPool.h"

uint32_t IDPool::generateID()
{
    uint32_t id = 0;
    //TODO: need to assert no dead loop
    while (id == 0 || exist(id)) {
        id = randomu32();
    }
    _pool.insert(id);
    return id;
}

bool IDPool::removeID(uint32_t id)
{
    if (!exist(id)) {
        return false;
    } else {
        _pool.erase(id);
        return true;
    }
    
    return false;
}

int IDPool::getSize()
{
    return _pool.size();
}

bool IDPool::exist(uint32_t id)
{
    bool ret = false;
    auto it = _pool.find(id);
    if (it != _pool.end()) {
        ret = true;
    }
    return ret;
}

// -- private --


uint32_t IDPool::randomu32()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    return (uint32_t)(mt());
}
