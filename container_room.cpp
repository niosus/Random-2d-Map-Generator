#include "container_room.h"
#include <qmath.h>

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

int ContainerRoom::holdingCapacity()
{
    int horizontalCapacity = 2 * qFloor(_xSize / UNIFIED_SIZE);
    int verticalCapacity = 2 * qFloor(_ySize / UNIFIED_SIZE);
    return horizontalCapacity + verticalCapacity;
}
