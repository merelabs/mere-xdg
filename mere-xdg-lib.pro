include(../../mere-utils/mere-utils-lib/mere-utils-lib.pri)
include(../../mere-store/mere-store-lib/mere-store-lib.pri)

QT      = core

CONFIG += c++11
CONFIG += shared

TARGET = mere-xdg
VERSION= 0.0.1
TEMPLATE = lib

DEFINES += LIB_CODE=\\\"xdg\\\"
DEFINES += LIB_NAME=\\\"$$TARGET\\\"
DEFINES += LIB_VERSION=\\\"$$VERSION\\\"
DEFINES += MERE_XDG_LIB

SOURCES += \
    src/autostartdirectoryspec.cpp \
    src/basedirectoryspec.cpp \
    src/desktopentry.cpp \
    src/desktopentrydirectoryspec.cpp \
    src/desktopentryspec.cpp \
    src/icontheme.cpp \
    src/iconthemedirectoryspec.cpp \
    src/iconthemespec.cpp

HEADERS += \
    src/autostartdirectoryspec.h \
    src/basedirectoryspec.h \
    src/desktopentry.h \
    src/desktopentrydirectoryspec.h \
    src/desktopentryspec.h \
    src/global.h \
    src/global.h \
    src/icontheme.h \
    src/iconthemedirectoryspec.h \
    src/iconthemespec.h

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib
LIBS += -lmere-utils


#
# Install
#
unix {
    target.path = /usr/local/lib
    INSTALLS += target

    INSTALL_PREFIX = /usr/local/include/mere/xdg
    for(header, HEADERS) {
        sdir = $${dirname(header)}
        sdir = $$replace(sdir, "src", "")
        path = $${INSTALL_PREFIX}$${sdir}

        eval(headers_$${path}.files += $$header)
        eval(headers_$${path}.path = $$path)
        eval(INSTALLS *= headers_$${path})
    }
}

