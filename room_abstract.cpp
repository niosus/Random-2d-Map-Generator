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

    updateBasicShape();
}

void AbstractRoom::updateBasicShape()
{
    _basicShape.clear();
    _basicShape[WALL_LEFT] = QLineF(_corners[LB], _corners[LT]);
    _basicShape[WALL_TOP] = QLineF(_corners[LT], _corners[RT]);
    _basicShape[WALL_RIGHT] = QLineF(_corners[RT], _corners[RB]);
    _basicShape[WALL_BOTTOM] = QLineF(_corners[RB], _corners[LB]);
}

QRectF AbstractRoom::boundingRect() const
{
    QPointF maxPoint(SMALL_NUM, SMALL_NUM);
    QPointF minPoint(BIG_NUM, BIG_NUM);
    for (const QString& key: _corners.keys())
    {
        if (_corners[key].x() > maxPoint.x())
        {
            maxPoint.setX(_corners[key].x());
        }
        if (_corners[key].y() > maxPoint.y())
        {
            maxPoint.setY(_corners[key].y());
        }
        if (_corners[key].x() < minPoint.x())
        {
            minPoint.setX(_corners[key].x());
        }
        if (_corners[key].y() < minPoint.y())
        {
            minPoint.setY(_corners[key].y());
        }
    }
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

