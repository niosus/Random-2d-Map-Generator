#include "simpleroom.h"

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

