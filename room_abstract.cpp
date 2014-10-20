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

int AbstractRoom::g_id = 0;

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
    this->setParentItem(NULL);
    _id = g_id++;
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
    return QRectF(minPoint, maxPoint);
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

bool AbstractRoom::intersectsSimple(const AbstractRoom* other) const
{
    if (this->boundingRect().intersects(other->boundingRect())) {
        return true;
    }
    return false;
}

bool AbstractRoom::intersectsPrecise(const AbstractRoom* other) const
{
    if (this == other->parentItem()
            || other == this->parentItem()) {
        /// these two have a healthy relationship
        /// they are allowed to touch each other and
        /// this doesn't cause a collision
        return false;
    }
    QPointF* dummy = NULL;
    for (const QLineF& line: _basicShape.values()) {
        for (const QLineF& lineOther: other->_basicShape.values()) {
            if(line.intersect(lineOther, dummy) == QLineF::BoundedIntersection) {
                return true;
            }
        }
    }
    return false;
}

// overriding attach functionIntersectsItemBoundingRect
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

//    this->itemChange(QGraphicsItem::ItemPositionChange, p1);

    qDebug() << "setting parrent for room" << this->id();
    this->setParentItem(parent);
}

// overriding detach function
void AbstractRoom::detach()
{
    this->setColor(Qt::red);
    _currentShape.clear();
}

void AbstractRoom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    QBrush b = painter->brush();
    painter->setBrush(Qt::white);
    painter->setPen(Qt::NoPen);
    painter->drawPath(shape());
    painter->setPen(QPen(_color, _penWidth, Qt::SolidLine, Qt::RoundCap));
    for (const QLineF& line: _currentShape)
    {
        painter->drawLine(line);
    }
    painter->setBrush(b);
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

int AbstractRoom::intersectsWithAnyInScene() const
{
    int intersections = 0;
    QList<QGraphicsItem *> items = this->collidingItems(Qt::IntersectsItemShape);
    for (QGraphicsItem * item: items)
    {
        AbstractRoom * room = dynamic_cast<AbstractRoom *>(item);
        if (!room) { continue; }
        if (room->intersectsPrecise(this)) {
            intersections++;
        }
    }
    return intersections;
}
