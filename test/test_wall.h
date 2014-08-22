#ifndef TEST_WALL_H
#define TEST_WALL_H

#include <QtTest/QtTest>
#include "wall.h"

class TestWall:
        public QObject
{
    Q_OBJECT
private slots:
    void testIntersection();
    void testTransform();
};

#endif // TEST_WALL_H
