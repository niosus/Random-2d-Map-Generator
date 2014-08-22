#include "test_first.h"

int main(int argc, char *argv[])
{
    TestFirst test1;
    QTest::qExec(&test1, argc, argv);

    return 0;
}
