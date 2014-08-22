#ifndef WALL_H
#define WALL_H

#include <QLineF>
#include <QPair>
#include <QTransform>
#include <QGraphicsItem>

class Wall: public QGraphicsItem
{
public:
    Wall(const qint64& id, const QPointF& p1, const QPointF& p2);

    bool intersectsWith(const Wall& other);

    void transform(const QTransform& transform);

    /// Overriding QGraphicsItem pure virtual methods
    virtual QRectF boundingRect() const;

    virtual void paint(
            QPainter * painter,
            const QStyleOptionGraphicsItem * option,
            QWidget * widget = 0);
    /// end of overriding QGraphicsItem

    // getters
    inline const QLineF& line()
    {
        return _line;
    }

private:
    void updateSpans();

    /// Coarse estimate of intersection.
    /// Based on AABB intersection.
    /// Final decision if not intersecting.
    /// If intersecting need further testing.
    bool intersectsCoarse(const Wall& other);

    /// Precise line intersection.
    bool intersectsPrecise(const Wall& other);


    /// Unique id
    qint64 _id;

    /// Underlying coordinates
    QLineF _line;

    /// Horizontal span for efficient intersection
    QPair<qreal, qreal> _xSpan;

    /// Vertical span for efficient intersection
    QPair<qreal, qreal> _ySpan;
};

#endif // WALL_H
