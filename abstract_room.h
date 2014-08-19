#ifndef TEST_RECT_H
#define TEST_RECT_H

#include <QColor>
#include <QGraphicsItem>
#include "attachable.h"

class AbstractRoom :
        public QGraphicsItem,
        public Attachable
{
public:
    AbstractRoom(const QColor &color, const qreal &w, const qreal &h);
    virtual ~AbstractRoom() { _currentShape.clear(); }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    // overriding the function attach
    void attach(const QPointF &p1, const QPointF &p2);

protected:
    virtual void updateCurrentPolygon();
    QPointF _lb; // left bottom corner
    QPointF _rt; // right top corner
    QPointF _lt; // left top corner
    QPointF _rb; // right bottom corner
    QColor _color;
    QVector<QLineF> _currentShape;

private:
    void transformCornersCoords();
};

#endif // TEST_RECT_H
