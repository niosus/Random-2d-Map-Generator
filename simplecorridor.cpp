#include "simplecorridor.h"

#include <QtWidgets>

SimpleCorridor::SimpleCorridor(const qreal &length, const qreal &width)
    :ContainerRoom(width, length) {
    _hasParent = false;
}


void SimpleCorridor::registerToScene(QGraphicsScene* scene)
{
    ContainerRoom::registerToScene(scene);
}

// Accounts for missing parts at connectors.
void SimpleCorridor::updateCurrentShape()
{
    if (!_currentShape.empty())
    {
        _currentShape.clear();
    }
    QPointF temp;
    // iterate through all walls
    for (const QString& tag: _basicShape.keys())
    {
        if (_hasParent && tag == WALL_BOTTOM)
        {
            continue;
        }
        temp = _basicShape[tag].p1();
        // if wall has connectors, make that visible
        for (Connector* connector: _connectorsPos[tag].values())
        {
            _currentShape.append(QLineF(temp, connector->first()));
            temp = connector->second();
        }
        _currentShape.append(QLineF(temp, _basicShape[tag].p2()));
    }
}
