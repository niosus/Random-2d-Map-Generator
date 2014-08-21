#ifndef SIMPLEROOM_H
#define SIMPLEROOM_H

#include <QColor>
#include "abstract_room.h"
#include <QVector>

class SimpleRoom :
        public AbstractRoom
{
public:
    SimpleRoom();
    virtual ~SimpleRoom() {}
    // overriding the function attach
    virtual void attach(const QPointF &p1, const QPointF &p2);

protected:
    // this function needs to be defined to override the drawn shape
    virtual void updateCurrentShape();

};

#endif // SIMPLEROOM_H
