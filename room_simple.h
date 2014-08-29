#ifndef SIMPLEROOM_H
#define SIMPLEROOM_H

#include <QColor>
#include "room_abstract.h"
#include <QVector>

class SimpleRoom :
        public AbstractRoom
{
public:
    SimpleRoom();
    virtual ~SimpleRoom() {}
    // overriding the function attach
    virtual void attach(
            const QPointF &p1,
            const QPointF &p2,
            QGraphicsItem *parent);

protected:
    // this function needs to be defined to override the drawn shape
    virtual void updateCurrentShape();

};

#endif // SIMPLEROOM_H
