#include "connector.h"
#include <iostream>

using namespace std;

Connector::Connector(
        const QLineF& parentLine,
        const QString& parentLineTag,
        const qreal &startOffset,
        const qreal &connectorSize)
{
    _parentLineTag = parentLineTag;
    _parentLine = parentLine;
    _startOffset = startOffset;
    qreal dOffset = connectorSize / parentLine.length();
    _endOffset = startOffset + dOffset;
}

QPointF Connector::first()
{
    return _parentLine.pointAt(_startOffset);
}

QPointF Connector::second()
{
    return _parentLine.pointAt(_endOffset);
}

void Connector::updateParentLine(const QLineF &parentLine)
{
    _parentLine = parentLine;
}