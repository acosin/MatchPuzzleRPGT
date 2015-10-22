//
//  IDPool.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include <set>

using namespace std;

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
    int randto(int n);
    void shuffle(unsigned *x, size_t n);
    uint32_t nrand32(int n);
};
