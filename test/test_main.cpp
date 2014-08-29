#include "test_connector.h"

int main(int argc, char *argv[])
{
    TestConnector testConnector;
    QTest::qExec(&testConnector, argc, argv);

    return 0;
}
