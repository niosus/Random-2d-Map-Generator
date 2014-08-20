#include "abstract_room.h"

#include <QtWidgets>

AbstractRoom::AbstractRoom()
{
    this->_color = Qt::black;
    this->_lb = QPointF(0, 0);
    this->_rt = _lb + QPointF(UNIFIED_SIZE, -UNIFIED_SIZE);
    this->_lt = _lb + QPointF(0, -UNIFIED_SIZE);
    this->_rb = _lb + QPointF(UNIFIED_SIZE, 0);

    setFlags(ItemIsSelectable);
    updateCurrentShape();
}

QRectF AbstractRoom::boundingRect() const
{
    return QRectF(_lb, _rt);
}

void AbstractRoom::transformCornersCoords()
{
    _lb = _transform.map(_lb);
    _rt = _transform.map(_rt);
    _lt = _transform.map(_lt);
    _rb = _transform.map(_rb);
}

// Just a П shape. Should be overridden.
void AbstractRoom::updateCurrentShape()
{
    if (!_currentShape.empty())
    {
        _currentShape.clear();
    }
    _currentShape.append(QLineF(_lb, _lt));
    _currentShape.append(QLineF(_lt, _rt));
    _currentShape.append(QLineF(_rt, _rb));
}

// overriding attach function
void AbstractRoom::attach(const QPointF &p1, const QPointF &p2)
{
    // first call the base class part
    Attachable::attach(p1, p2);
    // now build upon it
    transformCornersCoords();
    updateCurrentShape();
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

