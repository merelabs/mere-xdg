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
    void testset();
    void testevict();
};

#endif // TESTPARSER_H
