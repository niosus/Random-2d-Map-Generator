#ifndef CONTAINER_ROOM_H
#define CONTAINER_ROOM_H

#include "room_abstract.h"
#include "attachable.h"
#include "connector.h"

struct ContainerPositionStruct {
    QString _lineName;
    qreal _lineFraction;

    ContainerPositionStruct() {
        _lineName = "NONE";
        _lineFraction = 0;
    }

    ContainerPositionStruct(const QString& lineName, const qreal& lineFraction) {
        _lineName = lineName;
        _lineFraction = lineFraction;
    }
};


// A room that can contain other rooms
class ContainerRoom : public AbstractRoom
{
public:
    const static int CANNOT_ADD_CONNECTOR = -10;
    const static int CANNOT_ADD_ROOM = -11;

    ContainerRoom(
            const qreal &xSize,
            const qreal &ySize);
    virtual ~ContainerRoom();

    // needs to be updated to redraw children
    virtual void paint(
            QPainter *painter,
            const QStyleOptionGraphicsItem *item,
            QWidget *widget);

    int holdingCapacity();

    inline int currentFreeConnectors()
    {
        return _connectors.size() - _attachedRooms.size();
    }

    /// adds a connector to the specified line at the distance of
    /// connector.pos = lineFraction * line.length;
    /// @param lineTag       --> tag of the line to add connector to;
    /// @param lineFraction  --> double from [0,1] as fraction of line length;
    /// example in pseudo-code:
    /// addConnector(line({1,1} --> {2,2}), 0.5) will add a connector
    /// to position {1.5, 1.5}
    /// @return connector id if succeded, ERROR otherwise
    int addConnector(const QString &lineTag, const qreal &lineFraction);

    void removeEmptyConnector(const int id);

    void fillConnectorsWithRooms(const QVector<AbstractRoom*>& rooms);

    void reattachChildren();

    void updateConnectorPositions();

    /// overriding the function attach
    virtual void attach(
            const QPointF &p1,
            const QPointF &p2,
            QGraphicsItem *parent);

    virtual void detach();

    int addRoom(
            const QString &lineTag,
            const qreal &lineFraction,
            AbstractRoom* room);

    void removeRoom(const int roomId);

    int addRoomToConnector(const int connectorId, AbstractRoom* room);
protected:
    enum ConnectorState {
        FREE = 10,
        OCCUPIED = 11
    };

    // a function to update the shape to be drawn by paint()
    virtual void updateCurrentShape();

    AbstractRoom* findRoot();

    qreal _xSize;
    qreal _ySize;
    QMap<int, ConnectorState> _connectorStates;
    QHash<int, AbstractRoom *> _attachedRooms;
    QHash<int, Connector *> _connectors;
    QHash<QString, QMap<qreal, Connector*> > _connectorsPosOnLine;
    QHash<int, ContainerPositionStruct> _connectorPosById;

    /// <id_room> <id_connector> means that room is connected
    /// to the connector with corresponding ids.
    QHash<int, int> _roomConnectorPairs;

private:
    bool overlapsOtherConnectors(
            Connector* connector,
            const QString tag);
};

#endif // CONTAINER_ROOM_H
