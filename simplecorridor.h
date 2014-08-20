#ifndef SIMPLECORRIDOR_H
#define SIMPLECORRIDOR_H
#include <QColor>
#include "abstract_room.h"
#include <QVector>

class SimpleCorridor :
        public AbstractRoom
{
public:
    SimpleCorridor(const QColor &color, const qreal &w, const qreal &h);
    virtual ~SimpleCorridor() {}

protected:
    // this function needs to be defined to override the drawn shape
    void updateCurrentPolygon();

};

#endif // SIMPLECORRIDOR_H
