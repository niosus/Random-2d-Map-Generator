#ifndef CORRIDOR_RANDOM_H
#define CORRIDOR_RANDOM_H

#include "corridor_simple.h"

class CorridorRandom: public SimpleCorridor
{
public:
    CorridorRandom(const qreal &length,
                   const qreal &width = UNIFIED_SIZE);
};

#endif // CORRIDOR_RANDOM_H
