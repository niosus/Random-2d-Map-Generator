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

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    // overriding the function attach
    virtual void attach(
            const QPointF &p1,
            const QPointF &p2,
            AbstractRoom* parent = NULL);
    virtual void detach();

    virtual void registerToScene(QGraphicsScene* scene);

    virtual bool intersectsWith(const AbstractRoom* other) const;

    inline AbstractRoom* parent() const
    {
        return _parent;
    }

    void setColor(QColor color) { _color = color; }


    // span of the room along axes needed
    // for intersecting with others
    QPair<qreal, qreal> _horizontalSpan;
    QPair<qreal, qreal> _verticalSpan;

protected:
    // a function to update the shape to be drawn by paint()
    virtual void updateCurrentShape() = 0;

    virtual bool intersectsSimple(const AbstractRoom* other) const;

    virtual bool intersectsPrecise(const AbstractRoom* other) const;

    // corners of the room's basic shape
    QHash<QString, QPointF> _corners;

    // A set of lines that span a square
    // along the lines connecting the corners
    QHash<QString, QLineF> _basicShape;

    // The actual shape of the room to be drawn to screen.
    // Accounts for weird shapes and gaps in the room.
    // This shape is drawn by paint().
    QVector<QLineF> _currentShape;

    // The color to draw the shape with
    QColor _color;

    // The color to draw the shape with
    int _penWidth;

    // a standart size of the room
    static const qreal UNIFIED_SIZE;

    // corners' tags of the room's basic shape
    static const QString LB;
    static const QString RB;
    static const QString LT;
    static const QString RT;

    // names for walls in room frame (no transform)
    static const QString WALL_BOTTOM;
    static const QString WALL_TOP;
    static const QString WALL_LEFT;
    static const QString WALL_RIGHT;

    // A Convenience structure to transform all the points.
    // Holds pointers to all points.
    QVector<QPointF*> _allKeyPoints;


    // parent that this room is attached to
    AbstractRoom* _parent;

private:
    // transforms _allKeyPoints with a
    // given transform when the room gets attached
    void transform();
    void updateBasicShape();
    // needed for coarse intersection;
    void updateRoomSpans();
    // get bounds
    void getMinMax(QPointF& pMin, QPointF& pMax) const;
};

#endif // TEST_RECT_H
