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
        id = nrand32(UINT32_MAX);
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

int IDPool::randto(int n)
{
    int r;
    int maxrand = (RAND_MAX / n) * n;
    do r = rand(); while (r >= maxrand);
    return r % n;
}

void IDPool::shuffle(unsigned *x, size_t n)
{
    while (--n) {
        size_t j = randto(n + 1);
        unsigned tmp = x[n];
        x[n] = x[j];
        x[j] = tmp;
    }
}

uint32_t IDPool::nrand32(int n)
{
    uint32_t v = 0;
    static unsigned pos[32] = { 0,  1,  2,  3,  4,  5,  6,  7,
        8,  9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29, 30, 31};
    shuffle(pos, 32);
    while (n--) v |= (1U << pos[n]);
    return v;
}