#ifndef CONTAINER_ROOM_H
#define CONTAINER_ROOM_H

#include "abstract_room.h"
#include "attachable.h"

// A room that can contain other rooms
class ContainerRoom : public AbstractRoom
{
public:
    typedef QPair<QPointF, QPointF> Connector;
    ContainerRoom(
            const qreal &xSize,
            const qreal &ySize);
    virtual ~ContainerRoom();

protected:
    qreal _xSize;
    qreal _ySize;
    QVector<Attachable*> _children;
    QVector<Connector> _connectors;
};

#endif // CONTAINER_ROOM_H
