//
//  IDPool.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include <set>
#include <random>

using namespace std;

/*
 * NOTE: 0 not used!
 */
class IDPool
{
private:
    set<uint32_t> _pool;
    
public:
    uint32_t generateID();
    bool removeID(uint32_t id);
    int getSize();
    bool exist(uint32_t id);
    
private:
    uint32_t randomu32();
};
