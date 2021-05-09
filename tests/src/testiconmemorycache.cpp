#include "testiconmemorycache.h"
#include "mere/xdg/iconmemorycache.h"

void TestIconMemoryCache::initTestCase()
{
}

void TestIconMemoryCache::cleanupTestCase()
{
}

void TestIconMemoryCache::testset()
{
    Mere::XDG::IconMemoryCache cache(2);
    cache.set("a", "first character");

    QVERIFY(cache.get("a").compare("first character") == 0);
    bool set;
    QVERIFY(cache.get("a", &set).compare("first character") == 0);
    QVERIFY(set);
}

void TestIconMemoryCache::testevict()
{
    Mere::XDG::IconMemoryCache cache(2);
    cache.set("a", "first character");

    bool set;
    QVERIFY(cache.get("a", &set).compare("first character") == 0);
    QVERIFY(set);

    cache.set("b", "second character");
    cache.set("c", "third character");

    QVERIFY(cache.get("a", &set).compare("") == 0);
    QVERIFY(!set);
}
