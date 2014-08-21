#include <qmath.h>
#include <QVector2D>
#include <QDebug>
#include "container_room.h"

ContainerRoom::ContainerRoom(
        const qreal &xSize,
        const qreal &ySize)
    :AbstractRoom(xSize, ySize)
{
    this->_xSize = xSize;
    this->_ySize = ySize;
    updateCurrentShape();
}

ContainerRoom::~ContainerRoom()
{
    for (Attachable* attachable: _children)
    {
        attachable->detach();
        delete attachable;
        attachable = NULL;
    }
    for (Connector* connector: _connectors)
    {
        delete connector;
        connector = NULL;
    }
    _children.clear();
    _connectors.clear();
}

int ContainerRoom::holdingCapacity()
{
    int horizontalCapacity = 2 * qFloor(_xSize / UNIFIED_SIZE);
    int verticalCapacity = 2 * qFloor(_ySize / UNIFIED_SIZE);
    return horizontalCapacity + verticalCapacity;
}

void ContainerRoom::addConnector(const QString &lineTag, const qreal &lineFraction)
{
    Connector * connector = new Connector(
                _basicShape[lineTag],
                lineTag,
                lineFraction,
                UNIFIED_SIZE);

    // push the connector to vector
    _connectors.push_back(connector);
    // use the connector in vector from now on
    _connectorsPos[lineTag].insert(lineFraction, connector);

    updateCurrentShape();
}

void ContainerRoom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    AbstractRoom::paint(painter,option, widget);
    for (AbstractRoom* room: _children)
    {
        room->paint(painter, option, widget);
    }
}

// Accounts for missing parts at connectors.
void ContainerRoom::updateCurrentShape()
{
    if (!_currentShape.empty())
    {
        _currentShape.clear();
    }
    QPointF temp;
    // iterate through all walls
    for (const QString& tag: _basicShape.keys())
    {
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

void ContainerRoom::reattachChildren()
{
    int size = _children.size();
    for (int i = 0; i < size; ++i)
    {
        qDebug() << "attaching child " << i;
        _children[i]->attach(_connectors[i]->first(), _connectors[i]->second());
    }
}

void ContainerRoom::addRoomsToConnectors(const QVector<AbstractRoom*>& rooms)
{
    if (rooms.size() > currentFreeConnectors())
    {
        qDebug() << "we got more elements than we can store, will skip some of them";
    }
    int size = std::min(rooms.size(), currentFreeConnectors());
    for (int i = 0; i < size; ++i)
    {
        _children.append(rooms[i]);
        rooms[i]->attach(_connectors[i]->first(), _connectors[i]->second());
    }
}

void ContainerRoom::updateConnectorPositions()
{
    for (Connector* connector: _connectors)
    {
        connector->updateParentLine(_basicShape[connector->parentLineTag()]);
    }
}

// overriding the function attach
void ContainerRoom::attach(const QPointF &p1, const QPointF &p2)
{
    AbstractRoom::attach(p1, p2);
    this->updateConnectorPositions();
    this->reattachChildren();
    this->updateCurrentShape();
}

void ContainerRoom::registerToScene(QGraphicsScene* scene)
{
    AbstractRoom::registerToScene(scene);
    for (AbstractRoom* room: _children)
    {
        qDebug() << "registering";
        room->registerToScene(scene);
    }
}
