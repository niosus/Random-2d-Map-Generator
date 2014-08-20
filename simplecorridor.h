#ifndef SIMPLECORRIDOR_H
#define SIMPLECORRIDOR_H
#include <QColor>
#include <QVector>

#include "container_room.h"

class SimpleCorridor : public ContainerRoom
{
public:
    SimpleCorridor(const qreal &length,
                   const qreal &width = UNIFIED_SIZE);
    virtual ~SimpleCorridor() {}
    virtual void attach(const QPointF &p1, const QPointF &p2)
    {
        ContainerRoom::attach(p1, p2);
        _hasParent = true;
    }

    virtual void registerToScene(QGraphicsScene* scene);

protected:
    // a function to update the shape to be drawn by paint()
    virtual void updateCurrentShape();

private:
    bool _hasParent;

};

#endif // SIMPLECORRIDOR_H
