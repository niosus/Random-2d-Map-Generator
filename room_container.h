#ifndef CONTAINER_ROOM_H
#define CONTAINER_ROOM_H

#include "room_abstract.h"
#include "attachable.h"
#include "connector.h"

// A room that can contain other rooms
class ContainerRoom : public AbstractRoom
{
public:
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
        return _connectors.size() - _children.size();
    }

    // adds a connector to the specified line at the distance of
    // connector.pos = lineFraction * line.length;
    // @param lineTag       --> tag of the line to add connector to;
    // @param lineFraction  --> double from [0,1] as fraction of line length;
    // example in pseudo-code:
    // addConnector(line({1,1} --> {2,2}), 0.5) will add a connector
    // to position {1.5, 1.5}
    void addConnector(const QString &lineTag, const qreal &lineFraction);

    void addRoomsToConnectors(const QVector<AbstractRoom*>& rooms);

    void reattachChildren();

    void updateConnectorPositions();

    // overriding the function attach
    virtual void attach(
            const QPointF &p1,
            const QPointF &p2,
            AbstractRoom* parent = NULL);

    virtual void registerToScene(QGraphicsScene* scene);
protected:

    // a function to update the shape to be drawn by paint()
    virtual void updateCurrentShape();

    qreal _xSize;
    qreal _ySize;
    QVector<AbstractRoom*> _children;
    QVector<Connector*> _connectors;
    QHash<QString, QMap<qreal, Connector*> > _connectorsPos;

private:
    bool overlapsOtherConnectors(
            Connector* connector,
            const QString tag);
};

#endif // CONTAINER_ROOM_H
