#ifndef TESTPARSER_H
#define TESTPARSER_H

#include <QtTest>

class TestIconMemoryCache : public QObject
{
    Q_OBJECT
public:
    TestIconMemoryCache(){};
    ~TestIconMemoryCache(){};

private slots:
    void initTestCase();
    void cleanupTestCase();
};

#endif // TESTPARSER_H
