#include "testiconmemorycache.h"

int main(int argc, char** argv)
{
    int status = 0;
    {
        TestIconMemoryCache test;
        status |= QTest::qExec(&test, argc, argv);
    }
    return status;
}
