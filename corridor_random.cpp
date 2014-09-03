#include "corridor_random.h"
#include "room_builder.h"
#include <cstdlib>
#include <time.h>
#include <QDebug>

RandomCorridor::RandomCorridor(
        const qreal &length,
        const qreal &width,
        bool dominant)
    :SimpleCorridor(length, width)
{
    qsrand(time(0));
    int numRandCorridors = 0;
    for (int i = 0; i < this->holdingCapacity(); ++i)
    {
        qDebug() << "i: " << i;
        int randType = qrand()%100;
        qDebug() << "type " << randType;
        RoomBuilder::RoomType type;
        if (randType < 70)
        {
            type = RoomBuilder::SIMPLE_ROOM;
        } else if (randType < 90) {
            type = RoomBuilder::SIMPLE_CORRIDOR;
        } else if (numRandCorridors++ < 2 && dominant) {
            type = RoomBuilder::RANDOM_CORRIDOR;
            dominant = false;
        } else {
            type = RoomBuilder::SIMPLE_ROOM;
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
        qDebug() << "wall " << wallType;

        qreal frac = qrand() / (qreal) RAND_MAX;
        this->addRoom(wallType, frac, RoomBuilder::buildNewRoom(type, dominant));
    }
}
