#ifndef SIMPLEROOM_H
#define SIMPLEROOM_H

#include <QColor>
#include "abstract_room.h"
#include <QVector>

class SimpleRoom :
        public AbstractRoom
{
public:
    SimpleRoom();
    virtual ~SimpleRoom() {}

protected:
    // this function needs to be defined to override the drawn shape
    void updateCurrentShape();

};

#endif // SIMPLEROOM_H
