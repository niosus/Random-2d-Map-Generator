#ifndef TEST_CONNECTOR_H
#define TEST_CONNECTOR_H

#include <QObject>
#include <QtTest/QtTest>

class TestConnector : public QObject
{
    Q_OBJECT
public:
    explicit TestConnector(QObject *parent = 0);

signals:

public slots:

private slots:
    void testIds();
    void testAdd();

};

#endif // TEST_CONNECTOR_H
