#ifndef CORRIDOR_RANDOM_H
#define CORRIDOR_RANDOM_H

#include "corridor_simple.h"

class RandomCorridor: public SimpleCorridor
{
public:
    RandomCorridor(const qreal &length,
                   const qreal &width = UNIFIED_SIZE,
                   int numOfRandomCorridorsTillNow = 0);

protected:

    const int IMPORTANCE_WEIGHT = 3;
};

#endif // CORRIDOR_RANDOM_H
