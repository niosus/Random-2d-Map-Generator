#ifndef ATTACHABLE_H
#define ATTACHABLE_H

#include <QPointF>
#include <QTransform>

class Attachable
{
public:
    Attachable();
    virtual ~Attachable();
    virtual void attach(const QPointF &p1, const QPointF &p2);
    virtual void detach() = 0;

protected:
    QTransform _transform;
};

#endif // ATTACHABLE_H
