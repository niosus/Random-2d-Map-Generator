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
    AbstractRoom(
            qreal xSize = UNIFIED_SIZE,
            qreal ySize = UNIFIED_SIZE);
    virtual ~AbstractRoom() { _currentShape.clear(); }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    // overriding the function attach
    void attach(const QPointF &p1, const QPointF &p2);
    void detach();

protected:
    virtual void updateCurrentShape();
    QHash<QString, QPointF> _corners;
    QColor _color;
    QVector<QLineF> _currentShape;
    static const qreal UNIFIED_SIZE;
    static const QString LB;
    static const QString RB;
    static const QString LT;
    static const QString RT;

private:
    void transformCornersCoords();
};

#endif // TEST_RECT_H
