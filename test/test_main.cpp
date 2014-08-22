#include "test_wall.h"

int main(int argc, char *argv[])
{
    TestWall testWall;
    QTest::qExec(&testWall, argc, argv);

    return 0;
}
