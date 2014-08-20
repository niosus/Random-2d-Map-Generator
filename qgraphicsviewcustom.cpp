#include "qgraphicsviewcustom.h"
#include <QWheelEvent>

#include <QDebug>
#include <QScrollBar>

void QGraphicsViewCustom::wheelEvent(QWheelEvent* event)
{
    qreal factor = std::pow(1.001, event->delta());
    this->centerOn(mapToScene(event->pos()));
    this->scale(factor, factor);
    event->accept();
}

