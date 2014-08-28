#include <qmath.h>
#include <QVector2D>
#include <QDebug>
#include "room_container.h"

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

bool ContainerRoom::overlapsOtherConnectors(
        Connector* connector, const QString tag)
{
    //check if the connector intersects with other
    for (Connector* c: _connectorsPos[tag].values())
    {
        if (c->intersectsWith(connector))
        {
            // we cannot add a new connector;
            qDebug() << "ERROR: Cannot add a new connector, intersects with "<< c->first() << c->second();
            return true;
        }
    }
    return false;
}

void ContainerRoom::addConnector(const QString &lineTag, const qreal &lineFraction)
{
    Connector *connector = new Connector(
                _basicShape[lineTag],
                lineTag,
                lineFraction,
                UNIFIED_SIZE);
    if (overlapsOtherConnectors(connector, lineTag)) { return; }

    // push the connector to vector
    _connectors.push_back(connector);

    // add the connector
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
        _children[i]->attach(
                    _connectors[i]->first(),
                    _connectors[i]->second(),
                    this);
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
        rooms[i]->attach(
                    _connectors[i]->first(),
                    _connectors[i]->second(),
                    this);
        _children.append(rooms[i]);
    }
}

void ContainerRoom::updateConnectorPositions()
{
    for (Connector* connector: _connectors)
    {
        // this is needed to tell connector where it is in the world
        connector->updateParentLine(_basicShape[connector->parentLineTag()]);
    }
}

// overriding the function attach
void ContainerRoom::attach(
        const QPointF &p1,
        const QPointF &p2,
        QGraphicsItem* parent)
{
    AbstractRoom::attach(p1, p2, parent);
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

bool ContainerRoom::intersectsWith(const AbstractRoom* other) const
{
//    qDebug() << "checking intersection";
//    qDebug() << this->_horizontalSpan << this->_verticalSpan;
//    qDebug() << other->_horizontalSpan << other->_verticalSpan;
//    if (AbstractRoom::intersectsWith(other)) { return true; }
//    for (const AbstractRoom* room: _children)
//    {
//        if (room->intersectsWith(other))
//        {
//            return true;
//        }
//    }
    return false;
}
