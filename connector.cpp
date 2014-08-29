#include "connector.h"
#include <iostream>

using namespace std;

int Connector::_global_id = 0;

Connector::Connector(
        QLineF* parentLine,
        const QString& parentLineTag,
        const qreal &startOffset,
        const qreal &connectorSize)
{
    _parentLineTag = parentLineTag;
    _parentLine = parentLine;
    _startOffset = startOffset;
    qreal dOffset = connectorSize / parentLine->length();
    _endOffset = startOffset + dOffset;
    _current_id = _global_id++;
}

QPointF Connector::first()
{
    return _parentLine->pointAt(_startOffset);
}

QPointF Connector::second()
{
    return _parentLine->pointAt(_endOffset);
}

void Connector::updateParentLine(QLineF *parentLine)
{
    _parentLine = parentLine;
}

bool Connector::intersectsWith(const Connector* other)
{
    if (other->parentLineTag() != this->parentLineTag())
    {
        return false;
    }
    if (_startOffset < other->_endOffset
            && _endOffset > other->_startOffset)
    {
        return true;
    }
    return false;
}
