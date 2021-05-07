#include "testparser.h"

int main(int argc, char** argv)
{
    int status = 0;
    {
        TestParser test;
        status |= QTest::qExec(&test, argc, argv);
    }
    return status;
}
