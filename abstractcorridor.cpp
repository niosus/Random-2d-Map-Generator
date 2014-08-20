#include "abstractcorridor.h"

AbstractCorridor::AbstractCorridor(const qreal &length, const qreal &width)
    :AbstractRoom()
{
    this->_length = length;
    this->_width = width;
}
