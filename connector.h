#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QPointF>
#include <QLineF>
#include <QString>
#include <QDebug>

class Connector
{
public:
    Connector(QLineF *parentLine,
            const QString& parentLineTag,
            const qreal &startOffset,
            const qreal &connectorSize);

    QPointF first();
    QPointF second();

    void updateParentLine(QLineF *parentLine);

    bool intersectsWith(const Connector *other);

    inline const QString& parentLineTag() const
    {
        return _parentLineTag;
    }

    inline bool isValid() const
    {
        if (_startOffset > _endOffset) { return false; }
        if (_startOffset < 0 || _endOffset > 1.000001) { return false; }
        return true;
    }

    inline int id() const
    {
        return _current_id;
    }

private:
    QLineF* _parentLine;

    qreal _startOffset;
    qreal _endOffset;
    QString _parentLineTag;

    int _current_id;
    static int _global_id;
};

#endif // CONNECTOR_H
