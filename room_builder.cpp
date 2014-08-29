#include "room_builder.h"
#include "room_simple.h"
#include "corridor_simple.h"
#include "corridor_random.h"

RoomBuilder::RoomBuilder()
{
}

AbstractRoom* RoomBuilder::buildNewRoom(const RoomType type)
{
    switch (type) {
    case SIMPLE_ROOM:
        return new SimpleRoom;
    case SIMPLE_CORRIDOR:
        return new SimpleCorridor(500);
    case RANDOM_CORRIDOR:
        return new RandomCorridor(500);
    default:
        return NULL;
    }
}
