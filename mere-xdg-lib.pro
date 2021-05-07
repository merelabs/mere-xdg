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
    src/autostartdirectorytraverser.cpp \
    src/basedirectory.cpp \
    src/baseentry.cpp \
    src/config.cpp \
    src/desktopentry.cpp \
    src/desktopentryaction.cpp \
    src/desktopentrycategory.cpp \
    src/desktopentrydirectory.cpp \
    src/desktopentrydirectorytraverser.cpp \
    src/desktopentryparser.cpp \
    src/environment.cpp \
    src/icondirectorytraverser.cpp \
    src/iconlinkcache.cpp \
    src/iconlookuphelper.cpp \
    src/iconmemorycache.cpp \
    src/iconpathfinder.cpp \
    src/icontheme.cpp \
    src/iconthemecache.cpp \
    src/iconthemecontext.cpp \
    src/iconthemedirectory.cpp \
    src/iconthemedirectorytraverser.cpp \
    src/iconthemeparser.cpp \
    src/iconthemesubdirectory.cpp

HEADERS += \
    src/autostartdirectory.h \
    src/autostartdirectorytraverser.h \
    src/basedirectory.h \
    src/baseentry.h \
    src/config.h \
    src/desktopentry.h \
    src/desktopentryaction.h \
    src/desktopentrycategory.h \
    src/desktopentrydirectory.h \
    src/desktopentrydirectorytraverser.h \
    src/desktopentryparser.h \
    src/environment.h \
    src/global.h \
    src/global.h \
    src/icondirectorytraverser.h \
    src/iconlinkcache.h \
    src/iconlookuphelper.h \
    src/iconmemorycache.h \
    src/iconpathfinder.h \
    src/icontheme.h \
    src/iconthemecache.h \
    src/iconthemecontext.h \
    src/iconthemedirectory.h \
    src/iconthemedirectorytraverser.h \
    src/iconthemeparser.h \
    src/iconthemesubdirectory.h

DISTFILES += \
    etc/xdg.conf

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

