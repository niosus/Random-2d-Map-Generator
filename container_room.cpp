#include "container_room.h"

ContainerRoom::ContainerRoom(
        const qreal &xSize,
        const qreal &ySize)
    :AbstractRoom(xSize, ySize)
{
    this->_xSize = xSize;
    this->_ySize = ySize;
}

ContainerRoom::~ContainerRoom()
{
    for (Attachable* attachable: _children)
    {
        attachable->detach();
        delete attachable;
        attachable = NULL;
    }
}
