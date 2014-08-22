#include "test_wall.h"
#include <QDebug>

void TestWall::testIntersection()
{
    Wall w1(1, QPointF(1,1), QPointF(10,10));

    // intersects with self
    QCOMPARE(w1.intersectsWith(w1), true);

    Wall w2(2, QPointF(2,4), QPointF(4,6));

    // no intersection here
    QCOMPARE(w1.intersectsWith(w2), false);
    QCOMPARE(w2.intersectsWith(w1), false);

    Wall w3(3, QPointF(5,0), QPointF(5,10));

    // intersects
    QCOMPARE(w1.intersectsWith(w3), true);
    QCOMPARE(w3.intersectsWith(w1), true);

    // no intersection, they touch in endpoint
    Wall w4(4, QPointF(6,0), QPointF(0,0));
    QCOMPARE(w4.intersectsWith(w3), false);
    QCOMPARE(w3.intersectsWith(w4), false);

    Wall w5(5, QPointF(6,1), QPointF(0,0));
    // intersects
    QCOMPARE(w3.intersectsWith(w5), true);
    QCOMPARE(w5.intersectsWith(w3), true);

    Wall w6(6, QPointF(2.555,2.555), QPointF(10,-10));
    // no intersection, touch in {2.555, 2.555}
    QCOMPARE(w1.intersectsWith(w6), false);
    QCOMPARE(w6.intersectsWith(w1), false);
}

void TestWall::testTransform()
{
    QTransform dummy;
    dummy.translate(0, 0);
    QLineF result = QLineF(QPointF(1,1), QPointF(10,10));
    Wall w1(1, QPointF(1,1), QPointF(10,10));
    w1.transform(dummy);
    QCOMPARE(w1.line(), result);

    QTransform translate;
    translate.translate(1, 1);
    Wall w2(2, QPointF(1,1), QPointF(10,10));
    QLineF result2 = QLineF(QPointF(2,2), QPointF(11,11));
    w2.transform(translate);
    QCOMPARE(w2.line(), result2);

    QTransform rototranslate;
    rototranslate.translate(1, -1);
    rototranslate.rotate(-30);
    Wall w3(3, QPointF(1,1), QPointF(2,2));
    QLineF result3 = QLineF(
                QPointF(2.366025403784438, -0.633974596215561),
                QPointF(3.732050807568877, -0.267949192431123));
    // this is to test if the span is updated
    Wall w4(4, QPointF(3,-10), QPointF(3,10));
    QCOMPARE(w3.intersectsWith(w4), false);
    QCOMPARE(w4.intersectsWith(w3), false);
    w3.transform(rototranslate);
    QCOMPARE(w3.line(), result3);
    QCOMPARE(w3.intersectsWith(w4), true);
    QCOMPARE(w4.intersectsWith(w3), true);
}
