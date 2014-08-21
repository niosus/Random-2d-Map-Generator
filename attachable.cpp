#include "attachable.h"
#include <math.h>

Attachable::Attachable()
{
    _viewToWorld.reset();
    _worldToView.reset();
}

Attachable::~Attachable() {}

void Attachable::attach(
        const QPointF &p1,
        const QPointF &p2)
{
    // save the current state
    _worldToView = _viewToWorld.inverted();

    // set to identity
    _viewToWorld = QTransform();
    // construct new transform
    QPointF diff(p2 - p1);
    _viewToWorld.translate(p1.x(), p1.y());
    _viewToWorld.rotateRadians(atan2(diff.y(), diff.x()));
}

