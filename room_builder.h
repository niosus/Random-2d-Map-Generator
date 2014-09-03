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
                                      const bool dominant = true);

    RoomBuilder();
};

#endif // ROOM_BUILDER_H
