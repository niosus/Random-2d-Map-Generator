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
    for (AbstractRoom* attachable: _attachedRooms.values())
    {
        attachable->detach();
        delete attachable;
        attachable = NULL;
    }
    for (Connector* connector: _connectors.values())
    {
        delete connector;
        connector = NULL;
    }
    _attachedRooms.clear();
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
    for (Connector* c: _connectorsPosOnLine[tag].values())
    {
        if (c->intersectsWith(connector))
        {
            // we cannot add a new connector;
            qDebug() << "INFO: Cannot add a new connector, intersects with "<< c->first() << c->second();
            return true;
        }
    }
    return false;
}

int ContainerRoom::addRoom(
        const QString &lineTag,
        const qreal &lineFraction,
        AbstractRoom* room)
{
    int connectorId = this->addConnector(lineTag, lineFraction);
    if (connectorId == CANNOT_ADD_CONNECTOR) {
        return CANNOT_ADD_CONNECTOR;
    }
    int roomId = this->addRoomToConnector(connectorId, room);
    if (roomId == CANNOT_ADD_ROOM)
    {
        this->removeEmptyConnector(connectorId);
        return CANNOT_ADD_ROOM;
    }
    return roomId;
}

int ContainerRoom::addRoomToConnector(const int connectorId, AbstractRoom* room)
{
    if (_connectorStates[connectorId] != FREE) {
        qDebug() << "trying to add to a connector that is not free or doesn't exist";
        return CANNOT_ADD_ROOM;
    }
    _connectorStates.remove(connectorId);
    _roomConnectorPairs[room->id()] = connectorId;
    _attachedRooms[room->id()] = room;
    room->attach(
                _connectors[connectorId]->first(),
                _connectors[connectorId]->second(),
                this);
    if (room->intersectsWithAnyInScene()) {
        return CANNOT_ADD_ROOM;
    }
    return room->id();
}

void ContainerRoom::fillConnectorsWithRooms(const QVector<AbstractRoom*>& rooms)
{
    if (rooms.size() > currentFreeConnectors()) {
        qDebug() << "we got more elements than we can store, will skip some of them";
    }
    int size = std::min(rooms.size(), _connectorStates.size());
    int connectorId = -1;
    for (int i = 0; i < size; ++i) {
        connectorId = _connectorStates.keys().back();
        addRoomToConnector(connectorId, rooms[i]);
    }
}

int ContainerRoom::addConnector(const QString &lineTag, const qreal &lineFraction)
{
    Connector *connector = new Connector(
                &_basicShape[lineTag],
                lineTag,
                lineFraction,
                UNIFIED_SIZE);
    // check if we are overlapping any other connectors along the line
    if (overlapsOtherConnectors(connector, lineTag)) {
        return CANNOT_ADD_CONNECTOR;
    }
    if (!connector->isValid()) {
        /// Something is wrong with the connector
        return CANNOT_ADD_CONNECTOR;
    }

    // push the connector to vector
    _connectors.insert(connector->id(), connector);

    // add the connector
    _connectorsPosOnLine[lineTag].insert(lineFraction, connector);
    _connectorPosById.insert(
                connector->id(),
                ContainerPositionStruct(lineTag, lineFraction));

    // mark a connector as free
    _connectorStates[connector->id()] = FREE;

    updateCurrentShape();

    return connector->id();
}


void ContainerRoom::removeEmptyConnector(const int id)
{
    /// @todo this is ugly
    /// think of a better way to handle connectors
    /// or maybe even rooms as whole
    ///

    QString lineTag = _connectorPosById[id]._lineName;
    qreal lineFraction = _connectorPosById[id]._lineFraction;
    _connectorsPosOnLine[lineTag].remove(lineFraction);
    _connectorStates.remove(id);
    delete _connectors[id];
    _connectors.remove(id);
}


void ContainerRoom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    AbstractRoom::paint(painter,option, widget);
    for (AbstractRoom* room: _attachedRooms.values())
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
        for (Connector* connector: _connectorsPosOnLine[tag].values())
        {
            _currentShape.append(QLineF(temp, connector->first()));
            temp = connector->second();
        }
        _currentShape.append(QLineF(temp, _basicShape[tag].p2()));
    }
}

void ContainerRoom::reattachChildren()
{
    for (AbstractRoom *room: _attachedRooms.values())
    {
        int connectorId = _roomConnectorPairs[room->id()];
        Connector* connector = _connectors[connectorId];
        room->attach(connector->first(), connector->second(), this);
        if (room->intersectsWithAnyInScene()) {
            room->detach();
            _attachedRooms.remove(room->id());
            _roomConnectorPairs.remove(room->id());
            _connectors.remove(connectorId);
            removeEmptyConnector(connectorId);
            delete room;
        }
    }
}

void ContainerRoom::updateConnectorPositions()
{
    for (Connector* connector: _connectors.values())
    {
        // tell connector where it is in the world
        connector->updateParentLine(&_basicShape[connector->parentLineTag()]);
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

void ContainerRoom::detach() {
    for (AbstractRoom *room: _attachedRooms.values())
    {
        room->detach();
    }
    AbstractRoom::detach();
}
