#ifndef ATTACHABLE_H
#define ATTACHABLE_H

#include <QPointF>
#include <QTransform>

class Attachable
{
public:
    Attachable();
    virtual ~Attachable();

    /// Attach an attachable object to the line {p1, p2}
    /// @param p1: point to attach to.
    /// @param p2: point that defines the rotation of the line
    /// Rotation is defined by atan2, so order of p1 and p2 matters
    virtual void attach(const QPointF &p1, const QPointF &p2);
    virtual void detach() = 0;

protected:
    QTransform _viewToWorld;
    QTransform _worldToView;
};

#endif // ATTACHABLE_H
