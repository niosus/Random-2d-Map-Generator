#ifndef SIMPLEROOM_H
#define SIMPLEROOM_H

#include <QColor>
#include "abstract_room.h"
#include <QVector>

class SimpleRoom :
        public AbstractRoom
{
public:
    SimpleRoom(const QColor &color, const qreal &w, const qreal &h);
    virtual ~SimpleRoom() {}

protected:
    // this function needs to be defined to override the drawn shape
    void updateCurrentPolygon();

};

#endif // SIMPLEROOM_H
