#include "attachable.h"
#include <math.h>

Attachable::Attachable()
{
    _transform.reset();
}

Attachable::~Attachable() {}

void Attachable::attach(const QPointF &p1, const QPointF &p2)
{
    QPointF diff(p2 - p1);
    _transform.translate(p1.x(), -p1.y());
    _transform.rotateRadians(atan2(-fabs(diff.y()), fabs(diff.x())));
}

