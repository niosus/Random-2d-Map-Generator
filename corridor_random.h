#ifndef CORRIDOR_RANDOM_H
#define CORRIDOR_RANDOM_H

#include "corridor_simple.h"

class RandomCorridor: public SimpleCorridor
{
public:
    RandomCorridor(const qreal &length,
                   const qreal &width = UNIFIED_SIZE,
                   bool dominant = true);
};

#endif // CORRIDOR_RANDOM_H
