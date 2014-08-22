#ifndef TEST_FIRST_H
#define TEST_FIRST_H

#include <QtTest/QtTest>

class TestFirst: public QObject
{
    Q_OBJECT
private slots:
    void testing();
};
#endif // TEST_FIRST_H
