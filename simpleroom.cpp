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
    _currentShape.append(QLineF(_lb, _lb + 0.4 * (_rb - _lb)));
    _currentShape.append(QLineF(_lb, _lt));
    _currentShape.append(QLineF(_lt, _rt));
    _currentShape.append(QLineF(_rt, _rb));
    _currentShape.append(QLineF(_rb, _lb + 0.6 * (_rb - _lb)));
}

