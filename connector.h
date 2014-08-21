#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QPointF>
#include <QLineF>
#include <QString>

class Connector
{
public:
    Connector(
            const QLineF &parentLine,
            const QString& parentLineTag,
            const qreal &startOffset,
            const qreal &connectorSize);

    QPointF first();
    QPointF second();

    void updateParentLine(const QLineF &parentLine);

    bool intersectsWith(const Connector *other);

    inline const QString& parentLineTag() const
    {
        return _parentLineTag;
    }

private:
    QLineF _parentLine;

    qreal _startOffset;
    qreal _endOffset;
    QString _parentLineTag;
};

#endif // CONNECTOR_H
