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
    src/autostartdirectory.cpp \
    src/autostartdirectoryhelper.cpp \
    src/basedirectory.cpp \
    src/config.cpp \
    src/desktopentry.cpp \
    src/desktopentrydirectory.cpp \
    src/desktopentrydirectoryhelper.cpp \
    src/desktopentryhelper.cpp \
    src/desktopentryparser.cpp \
    src/iconlinkcache.cpp \
    src/iconlookuphelper.cpp \
    src/iconpathfinder.cpp \
    src/icontheme.cpp \
    src/iconthemecache.cpp \
    src/iconthemecontext.cpp \
    src/iconthemedirectory.cpp \
    src/iconthemehelper.cpp \
    src/iconthemesubdirectory.cpp \
    src/iconthemesubdirectoryhelper.cpp

HEADERS += \
    src/autostartdirectory.h \
    src/autostartdirectoryhelper.h \
    src/basedirectory.h \
    src/config.h \
    src/desktopentry.h \
    src/desktopentrydirectory.h \
    src/desktopentrydirectoryhelper.h \
    src/desktopentryhelper.h \
    src/desktopentryparser.h \
    src/global.h \
    src/global.h \
    src/iconlinkcache.h \
    src/iconlookuphelper.h \
    src/iconpathfinder.h \
    src/icontheme.h \
    src/iconthemecache.h \
    src/iconthemecontext.h \
    src/iconthemedirectory.h \
    src/iconthemehelper.h \
    src/iconthemesubdirectory.h \
    src/iconthemesubdirectoryhelper.h

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib

LIBS += -lmere-config-lite -lmere-utils

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

