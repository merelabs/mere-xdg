QT += testlib
QT -= gui

CONFIG += qt console
CONFIG -= app_bundle
CONFIG += no_testcase_installs
CONFIG += object_parallel_to_source

TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/testiconmemorycache.cpp

HEADERS += \
    src/testiconmemorycache.h

include(../mere-xdg-src.pri)

INCLUDEPATH += /usr/local/include

