#include "abstract_room.h"

#include <QtWidgets>

#define SMALL_NUM {std::numeric_limits<double>::min()}
#define BIG_NUM {std::numeric_limits<double>::max()}

const qreal AbstractRoom::UNIFIED_SIZE = 100;
const QString AbstractRoom::LB = "lb";
const QString AbstractRoom::RB = "rb";
const QString AbstractRoom::LT = "lt";
const QString AbstractRoom::RT = "rt";

AbstractRoom::AbstractRoom(qreal xSize, qreal ySize)
{
    _color = Qt::black;
    _corners[LB] = QPointF(0, 0);
    _corners[RT] = _corners[LB] + QPointF(xSize, -ySize);
    _corners[LT] = _corners[LB] + QPointF(0, -ySize);
    _corners[RB] = _corners[LB] + QPointF(xSize, 0);

    for (const QString& key:_corners.keys())
    {
        _allKeyPoints.append(&_corners[key]);
    }

    updateCurrentShape();
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

void AbstractRoom::transformCornersCoords()
{
    for (const QString& key: _corners.keys())
    {
        _corners[key] = _transform.map(_corners[key]);
    }
}

void AbstractRoom::transform()
{
    for (QPointF* point: _allKeyPoints)
    {
        *point = _transform.map(*point);
    }
}

// Just a П shape. Should be overridden.
void AbstractRoom::updateCurrentShape()
{
    if (!_currentShape.empty())
    {
        _currentShape.clear();
    }
    _currentShape.append(QLineF(_corners[LB], _corners[LT]));
    _currentShape.append(QLineF(_corners[LT], _corners[RT]));
    _currentShape.append(QLineF(_corners[RT], _corners[RB]));
}

// overriding attach function
void AbstractRoom::attach(const QPointF &p1, const QPointF &p2)
{
    // first call the base class part
    Attachable::attach(p1, p2);
    // now build upon it
    this->transform();
    this->updateCurrentShape();
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
    painter->setPen(QPen(_color, 3, Qt::SolidLine, Qt::RoundCap));
    for (const QLineF& line: _currentShape)
    {
        painter->drawLine(line);
    }
    painter->setBrush(b);
}

