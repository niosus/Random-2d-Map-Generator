#include "simpleroom.h"

#include <QtWidgets>

SimpleRoom::SimpleRoom(const QColor &color, const qreal &w, const qreal &h)
    : AbstractRoom(color, w, h)
{
    this->_color = color;
    this->_lb = QPointF(0, 0);
    this->_rt = _lb + QPointF(w, -h);
    this->_lt = _lb + QPointF(0, -h);
    this->_rb = _lb + QPointF(w, 0);

    setFlags(ItemIsSelectable);
    updateCurrentPolygon();
}

void SimpleRoom::updateCurrentPolygon()
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

