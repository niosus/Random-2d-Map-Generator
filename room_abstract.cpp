#include "room_abstract.h"

#include <QtWidgets>

#define SMALL_NUM {std::numeric_limits<double>::min()}
#define BIG_NUM {std::numeric_limits<double>::max()}

const qreal AbstractRoom::UNIFIED_SIZE = 100;
const QString AbstractRoom::LB = "lb";
const QString AbstractRoom::RB = "rb";
const QString AbstractRoom::LT = "lt";
const QString AbstractRoom::RT = "rt";

const QString AbstractRoom::WALL_BOTTOM = "wb";
const QString AbstractRoom::WALL_TOP = "wt";
const QString AbstractRoom::WALL_LEFT = "wl";
const QString AbstractRoom::WALL_RIGHT = "wr";

AbstractRoom::AbstractRoom(
        qreal xSize,
        qreal ySize)
{
    _color = Qt::black;
    _penWidth = 5;
    _corners[LB] = QPointF(0, 0);
    _corners[RT] = _corners[LB] + QPointF(xSize, -ySize);
    _corners[LT] = _corners[LB] + QPointF(0, -ySize);
    _corners[RB] = _corners[LB] + QPointF(xSize, 0);
    this->setPos(_corners[LB]);
    for (const QString& key:_corners.keys())
    {
        _allKeyPoints.append(&_corners[key]);
    }

    this->updateBasicShape();
    this->updateRoomSpans();
    this->setParentItem(NULL);
}

void AbstractRoom::updateBasicShape()
{
    _basicShape.clear();
    _basicShape[WALL_LEFT] = QLineF(_corners[LB], _corners[LT]);
    _basicShape[WALL_TOP] = QLineF(_corners[LT], _corners[RT]);
    _basicShape[WALL_RIGHT] = QLineF(_corners[RT], _corners[RB]);
    _basicShape[WALL_BOTTOM] = QLineF(_corners[RB], _corners[LB]);
}

void AbstractRoom::getMinMax(QPointF& pMin, QPointF& pMax) const
{
    pMax = QPointF(SMALL_NUM, SMALL_NUM);
    pMin = QPointF(BIG_NUM, BIG_NUM);
    for (const QString& key: _corners.keys())
    {
        if (_corners[key].x() > pMax.x())
        {
            pMax.setX(_corners[key].x());
        }
        if (_corners[key].y() > pMax.y())
        {
            pMax.setY(_corners[key].y());
        }
        if (_corners[key].x() < pMin.x())
        {
            pMin.setX(_corners[key].x());
        }
        if (_corners[key].y() < pMin.y())
        {
            pMin.setY(_corners[key].y());
        }
    }
}

QRectF AbstractRoom::boundingRect() const
{
    QPointF maxPoint(SMALL_NUM, SMALL_NUM);
    QPointF minPoint(BIG_NUM, BIG_NUM);
    getMinMax(minPoint, maxPoint);
    QPointF size = maxPoint-minPoint;
    size.setX(fabs(size.x()) + 50);
    size.setY(fabs(size.y()) + 50);
    return QRectF(minPoint, size);
}

void AbstractRoom::transform()
{
    for (QPointF* point: _allKeyPoints)
    {
        // move the point back to local coordinates
        // with a stored inverted transformation
        *point = _worldToView.map(*point);
        // translate to the new pos in the world
        *point = _viewToWorld.map(*point);
    }
}

void AbstractRoom::updateRoomSpans()
{
    QPointF maxPoint(SMALL_NUM, SMALL_NUM);
    QPointF minPoint(BIG_NUM, BIG_NUM);
    getMinMax(minPoint, maxPoint);
    _horizontalSpan.first = minPoint.x();
    _horizontalSpan.second = maxPoint.x();
    _verticalSpan.first = minPoint.y();
    _verticalSpan.second = maxPoint.y();
    qDebug() << _horizontalSpan << _verticalSpan;
}

bool AbstractRoom::intersectsWith(const AbstractRoom* other) const
{
    // simple AABB intersection
    if (!this->intersectsSimple(other))
    {
        // even the simple coarse intersection
        // did not trigger, so no intersection.
        return false;
    }
    // intersects coarsely, so let's check
    // if precise intersection works
    if (this->intersectsPrecise(other))
    {
        // yes, they do intersect indeed
        return true;
    }
    // their bounding boxes intersect,
    // but not the actual objects
    return false;
}

bool AbstractRoom::intersectsSimple(const AbstractRoom* other) const
{
    return this->collidesWithItem(other, Qt::IntersectsItemBoundingRect);
}

bool AbstractRoom::intersectsPrecise(const AbstractRoom* other) const
{
    QPointF intersection;
    for (const QLineF& line: _basicShape.values())
    {
        for (const QLineF& lineOther: other->_basicShape.values())
        {
            if(line.intersect(lineOther, &intersection) == QLineF::BoundedIntersection)
            {
                if (line.p1() == intersection
                        || line.p2() == intersection
                        || lineOther.p1() == intersection
                        || lineOther.p2() == intersection)
                {
                    // they don't intersect, just touch.
                    // touching is not a crime
                    return false;
                }
                return true;
            }
        }
    }
    return false;
}

// overriding attach function
void AbstractRoom::attach(
        const QPointF &p1,
        const QPointF &p2,
        QGraphicsItem *parent)
{
    // first call the base class part
    Attachable::attach(p1, p2);
    // transform all point
    this->transform();
    // shapes have to be updated as the
    // points have changed coordinates
    this->updateBasicShape();

    this->updateRoomSpans();

    this->setParentItem(parent);
    this->itemChange(QGraphicsItem::ItemPositionChange, _corners[LB]);
}

// overriding attach function
void AbstractRoom::detach()
{
    _currentShape.clear();
}

void AbstractRoom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    QBrush b = painter->brush();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(_color, _penWidth, Qt::SolidLine, Qt::RoundCap));
    for (const QLineF& line: _currentShape)
    {
        painter->drawLine(line);
    }
    painter->setBrush(b);
}

void AbstractRoom::registerToScene(QGraphicsScene* scene)
{
    scene->addItem(this);
    QList<QGraphicsItem *> items = this->collidingItems();
    if (items.empty()) {
        // no colliding items
        return;
    } else {
        for (QGraphicsItem *item: items)
        {
            AbstractRoom *room = dynamic_cast<AbstractRoom *>(item);
            if (!room)
            {
                continue;
            }
            if (this->intersectsPrecise(room))
            {
                this->setColor(Qt::red);
                return;
            }
        }

    }
}

QPainterPath AbstractRoom::shape() const
{
    QPainterPath path;
    QPolygonF polygon;
    polygon.append(_corners[LB]);
    polygon.append(_corners[LT]);
    polygon.append(_corners[RT]);
    polygon.append(_corners[RB]);
    polygon.append(_corners[LB]);
    path.addPolygon(polygon);
    return path;
}

QVariant AbstractRoom::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        qDebug() << "position has changed";
    }
    return QGraphicsItem::itemChange(change, value);
}

