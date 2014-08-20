#ifndef ABSTRACTCORRIDOR_H
#define ABSTRACTCORRIDOR_H

#include <QVector>
#include <QPointF>
#include <QPair>

#include "abstract_room.h"

class AbstractCorridor : public AbstractRoom
{
public:
    typedef QVector<QPair<QPointF, QPointF> > Gates;
    AbstractCorridor(
            const qreal &length,
            const qreal &width);
    virtual ~AbstractCorridor() {}

    inline Gates* getRoomPlaces() {
        return &_gates;
    }

protected:
    Gates _gates;
    qreal _length;
    qreal _width;
};

#endif // ABSTRACTCORRIDOR_H
