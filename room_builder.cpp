#include "room_builder.h"
#include "room_simple.h"
#include "corridor_simple.h"
#include "corridor_random.h"
#include <QTime>

int RoomBuilder::g_numberOfRandomCorridors = 0;

RoomBuilder::RoomBuilder() {
}

void RoomBuilder::reInit() {
    g_numberOfRandomCorridors = 0;
}

AbstractRoom* RoomBuilder::buildNewRoom(const RoomType type)
{
    switch (type) {
    case SIMPLE_ROOM:
        return new SimpleRoom;
    case SIMPLE_CORRIDOR:
        return new SimpleCorridor(500);
    case RANDOM_CORRIDOR:
        if (++g_numberOfRandomCorridors > MAX_ALLOWED_RAND_CORRIDORS) {
            return new SimpleRoom();
        }
        return new RandomCorridor(800, 100);
    default:
        return NULL;
    }
}
