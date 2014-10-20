#ifndef ROOM_BUILDER_H
#define ROOM_BUILDER_H

#include "room_abstract.h"

class RoomBuilder
{
public:
    enum RoomType {
        SIMPLE_ROOM,
        SIMPLE_CORRIDOR,
        RANDOM_CORRIDOR,
        RANDOM_GALLERY
    };

    static void reInit();

    static AbstractRoom* buildNewRoom(const RoomType type);

    RoomBuilder();

private:
    static const int MAX_ALLOWED_RAND_CORRIDORS = 5;
    static const int MAX_ALLOWED_RAND_GALLERIES = 1;

    static int g_numberOfRandomCorridors;
    static int g_numberOfRandomGalleries;

};

#endif // ROOM_BUILDER_H
