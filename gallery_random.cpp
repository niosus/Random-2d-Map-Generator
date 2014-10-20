#include "gallery_random.h"
#include "room_builder.h"
#include <cstdlib>
#include <time.h>
#include <QDebug>
#include <QBrush>
#include <QPainter>

RandomGallery::RandomGallery(const qreal &length,
        const qreal &width)
    :RandomCorridor(length, width) {}

void RandomGallery::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    RandomCorridor::paint(painter, option, widget);
    QBrush b = painter->brush();
    painter->setBrush(Qt::gray);
    painter->drawRect(_currentInnerShape);
    painter->setBrush(b);
}

// Accounts for missing parts at connectors.
void RandomGallery::updateCurrentShape()
{
    RandomCorridor::updateCurrentShape();
    /// update the inner shape of the gallery
    _currentInnerShape = QRectF(_basicShape[WALL_LEFT].p1(), _basicShape[WALL_RIGHT].p1());
    _currentInnerShape.setSize(_currentInnerShape.size() - QSizeF(2 * UNIFIED_SIZE, 2 * UNIFIED_SIZE));
    _currentInnerShape.moveCenter(_currentInnerShape.center() + QPointF(UNIFIED_SIZE, UNIFIED_SIZE));
}
