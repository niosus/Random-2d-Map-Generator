#ifndef GALLERY_RANDOM_H
#define GALLERY_RANDOM_H

#include "corridor_random.h"

class RandomGallery: public RandomCorridor
{
public:
    RandomGallery(const qreal &length = 6 * UNIFIED_SIZE,
                   const qreal &width = 6 * UNIFIED_SIZE);

    // needs to be updated to redraw children
    virtual void paint(
            QPainter *painter,
            const QStyleOptionGraphicsItem *item,
            QWidget *widget);

protected:
    const int IMPORTANCE_WEIGHT = 3;

    // The actual shape of the room to be drawn to screen.
    // Accounts for weird shapes and gaps in the room.
    // This shape is drawn by paint().
    QRectF _currentInnerShape;

    // a function to update the shape to be drawn by paint()
    virtual void updateCurrentShape();
};

#endif // GALLERY_RANDOM_H
