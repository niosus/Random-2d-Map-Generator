#include "corridor_random.h"
#include "room_builder.h"
#include <cstdlib>
#include <time.h>

RandomCorridor::RandomCorridor(
        const qreal &length,
        const qreal &width)
    :SimpleCorridor(length, width)
{
    qsrand(3);
    for (int i = 0; i < this->holdingCapacity(); ++i)
    {
        int randType = qrand()%100;
        RoomBuilder::RoomType type;
        if (randType < 70)
        {
            type = RoomBuilder::SIMPLE_ROOM;
        } else if (randType < 90) {
            type = RoomBuilder::SIMPLE_CORRIDOR;
        } else {
            type = RoomBuilder::RANDOM_CORRIDOR;
        }

        const int randWall = qrand() % 4;
        QString wallType = "";
        switch (randWall)
        {
        case 0:
            wallType = AbstractRoom::WALL_BOTTOM;
            break;
        case 1:
            wallType = AbstractRoom::WALL_LEFT;
            break;
        case 2:
            wallType = AbstractRoom::WALL_TOP;
            break;
        case 3:
            wallType = AbstractRoom::WALL_RIGHT;
            break;
        }

        qreal frac = qrand() / (qreal) RAND_MAX;
        this->addRoom(wallType, frac, RoomBuilder::buildNewRoom(type));
    }
}
