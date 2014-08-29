#include "test_connector.h"
#include "corridor_simple.h"

TestConnector::TestConnector(QObject *parent) :
    QObject(parent)
{
}

void TestConnector::testAdd()
{
    SimpleCorridor* corridor = new SimpleCorridor(500);
    QCOMPARE(corridor->addConnector(AbstractRoom::WALL_LEFT, 0.5), true);
    QCOMPARE(corridor->addConnector(AbstractRoom::WALL_LEFT, 0.5), false);
    QCOMPARE(corridor->addConnector(AbstractRoom::WALL_LEFT, 0.9), false);
    QCOMPARE(corridor->addConnector(AbstractRoom::WALL_TOP, 0.5), false);
    QCOMPARE(corridor->addConnector(AbstractRoom::WALL_TOP, 0), true);
    QCOMPARE(corridor->addConnector(AbstractRoom::WALL_BOTTOM, 0), true);
}

void TestConnector::testIds()
{
    QLineF line(QPointF(0,0), QPointF(10, 10));
    Connector connector1(&line, "hello", 0, 1);
    QCOMPARE(connector1.id(), 0);
    Connector connector2(&line, "hello", 0, 1);
    QCOMPARE(connector2.id(), 1);
}
