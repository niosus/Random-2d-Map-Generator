#include "simplecorridor.h"

#include <QtWidgets>

SimpleCorridor::SimpleCorridor(const qreal &length, const qreal &width)
    :ContainerRoom(width, length) {}


void SimpleCorridor::registerToScene(QGraphicsScene* scene)
{
    ContainerRoom::registerToScene(scene);
}
