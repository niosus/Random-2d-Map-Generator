#include "wall.h"
#include <QDebug>

Wall::Wall(const qint64 &id, const QPointF &p1, const QPointF &p2)
{
    _id = id;
    _line = QLineF(p1, p2);
    this->updateSpans();
}

void Wall::updateSpans()
{
    _xSpan.first = std::min(_line.p1().x(), _line.p2().x());
    _xSpan.second = std::max(_line.p1().x(), _line.p2().x());
    _ySpan.first = std::min(_line.p1().y(), _line.p2().y());
    _ySpan.second = std::max(_line.p1().y(), _line.p2().y());
}

bool Wall::intersectsWith(const Wall& other)
{
    if (this->_line == other._line) {
        return true;
    }
    if (intersectsCoarse(other))
    {
        if (intersectsPrecise(other))
        {
            return true;
        }
    }
    return false;
}

bool Wall::intersectsCoarse(const Wall& other)
{
    bool horOverlap = this->_xSpan.second > other._xSpan.first
            && this->_xSpan.first < other._xSpan.second;
    bool verOverlap = this->_ySpan.second > other._ySpan.first
            && this->_ySpan.first < other._ySpan.second;
    if (horOverlap || verOverlap)
    {
        return true;
    }
    return false;
}

bool Wall::intersectsPrecise(const Wall& other)
{
    QPointF intersection;
    if (this->_line.intersect(other._line, &intersection)
            == QLineF::BoundedIntersection)
    {
        if (this->_line.p1() == intersection
                || this->_line.p2() == intersection
                || other._line.p1() == intersection
                || other._line.p2() == intersection)
        {
            // they don't intersect, just touch.
            // touching is not a crime
            return false;
        }
        // intersect
        return true;
    }
    return false;
}

void Wall::transform(const QTransform& transform)
{
    _line = transform.map(_line);
    this->updateSpans();
}


QRectF Wall::boundingRect() const
{
    /// very-very coarse. maybe do other way?
    return (QRectF(
                QPointF(_xSpan.first, _ySpan.first),
                QPointF(_xSpan.second, _ySpan.second)));
}

void Wall::paint(
        QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget)
{
    // TODO: this needs to draw the wall. Will be drawn by paint method of room
}
