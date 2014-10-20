#ifndef ROOM_BUILDER_H
#define ROOM_BUILDER_H

#include "room_abstract.h"

class RoomBuilder
{
public:
    enum RoomType {
        SIMPLE_ROOM,
        SIMPLE_CORRIDOR,
        RANDOM_CORRIDOR
    };

    static AbstractRoom* buildNewRoom(const RoomType type,
                                      int numOfRandomCorridors = true);

    RoomBuilder();

private:
    static const int MAX_ALLOWED_RAND_CORRIDORS = 5;
};

#endif // ROOM_BUILDER_H
