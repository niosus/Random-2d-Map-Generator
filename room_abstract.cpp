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

AbstractRoom::AbstractRoom(qreal xSize, qreal ySize)
{
    _parent = NULL;
    _color = Qt::black;
    _penWidth = 5;
    _corners[LB] = QPointF(0, 0);
    _corners[RT] = _corners[LB] + QPointF(xSize, -ySize);
    _corners[LT] = _corners[LB] + QPointF(0, -ySize);
    _corners[RB] = _corners[LB] + QPointF(xSize, 0);

    for (const QString& key:_corners.keys())
    {
        _allKeyPoints.append(&_corners[key]);
    }

    this->updateBasicShape();
    this->updateRoomSpans();
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
    // if we are a parent of other,
    // makes no sense to intersect
    if (other->_parent == this) { return false; }
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
    if (other->_horizontalSpan.first < other->_horizontalSpan.second
            && other->_horizontalSpan.second > other->_horizontalSpan.first)
    {
        return true;
    }
    return false;
}

bool AbstractRoom::intersectsPrecise(const AbstractRoom* other) const
{
    QPointF* dummy = NULL;
    for (const QLineF& line: _basicShape.values())
    {
        for (const QLineF& lineOther: other->_basicShape.values())
        {
            if(line.intersect(lineOther, dummy) == QLineF::BoundedIntersection)
            {
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
        AbstractRoom *parent)
{
    // first call the base class part
    Attachable::attach(p1, p2);
    // transform all point
    this->transform();
    // shapes have to be updated as the
    // points have changed coordinates
    this->updateBasicShape();

    //set parent
    _parent = parent;

    this->updateRoomSpans();
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
}

