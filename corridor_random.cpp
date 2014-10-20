#include "corridor_random.h"
#include "room_builder.h"
#include <cstdlib>
#include <time.h>
#include <QDebug>

RandomCorridor::RandomCorridor(const qreal &length,
        const qreal &width)
    :SimpleCorridor(length, width)
{
    int i = 0;
    while (i++ < this->holdingCapacity() / 2) {
        qDebug() << "i: " << i;
        int randType = qrand()%100;
        RoomBuilder::RoomType type;
        if (randType < 50)
        {
            type = RoomBuilder::RANDOM_CORRIDOR;
        } else if (randType < 60) {
            type = RoomBuilder::SIMPLE_CORRIDOR;
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

        qreal frac = qrand() / (qreal) RAND_MAX;
        int resultCode = this->addRoom(wallType, frac,
                      RoomBuilder::buildNewRoom(type));

        // if we failed to add a room, we want to try again
        if (resultCode == CANNOT_ADD_ROOM ||
                resultCode == CANNOT_ADD_CONNECTOR) {
            i--;
        }
    }
}
