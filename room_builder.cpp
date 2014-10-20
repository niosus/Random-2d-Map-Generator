#include "room_builder.h"
#include "room_simple.h"
#include "corridor_simple.h"
#include "corridor_random.h"
#include <QTime>

RoomBuilder::RoomBuilder() {
}

AbstractRoom* RoomBuilder::buildNewRoom(const RoomType type,
                                        int numOfRandomCorridors)
{
    switch (type) {
    case SIMPLE_ROOM:
        return new SimpleRoom;
    case SIMPLE_CORRIDOR:
        return new SimpleCorridor(500);
    case RANDOM_CORRIDOR:
        if (++numOfRandomCorridors > MAX_ALLOWED_RAND_CORRIDORS) {
            return new SimpleRoom();
        }
        return new RandomCorridor(500, 100, numOfRandomCorridors);
    default:
        return NULL;
    }
}
