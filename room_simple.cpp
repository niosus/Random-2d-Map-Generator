#include "room_simple.h"

#include <QtWidgets>

SimpleRoom::SimpleRoom()
    : AbstractRoom() {}

void SimpleRoom::updateCurrentShape()
{
    if (!_currentShape.empty())
    {
        _currentShape.clear();
    }
    _currentShape.append(QLineF(_corners[LB], _corners[LB] + 0.3 * (_corners[RB] - _corners[LB])));
    _currentShape.append(QLineF(_corners[LB], _corners[LT]));
    _currentShape.append(QLineF(_corners[LT], _corners[RT]));
    _currentShape.append(QLineF(_corners[RT], _corners[RB]));
    _currentShape.append(QLineF(_corners[RB], _corners[LB] + 0.7 * (_corners[RB] - _corners[LB])));
}

// overriding attach function
void SimpleRoom::attach(
        const QPointF &p1,
        const QPointF &p2,
        QGraphicsItem* parent)
{
    // first call the base class part
    AbstractRoom::attach(p1, p2, parent);
    this->updateCurrentShape();
}

