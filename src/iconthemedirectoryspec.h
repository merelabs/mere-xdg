#ifndef MERE_XDG_ICONTHEMEDIRECTORYSPEC_H
#define MERE_XDG_ICONTHEMEDIRECTORYSPEC_H

#include "global.h"

namespace Mere
{
namespace XDG
{
static const char* ICON_DIRECTORY = "icons";

class MERE_XDG_LIB_SPEC IconThemeDirectorySpec
{
public:
    IconThemeDirectorySpec();

    static QString userIconDirectory();

    /**
     * @brief iconDirectories
     *
     * Directories where system will search for icon theme files.
     *
     * @return
     */
    static QStringList baseDirectories();
    static QString iconDirectory(const QString &path);

    static QStringList themeDirectories(const QString &theme);

    // move to a commoon place
    static void expandEnvVars(QString &path);

private:
    // move to a commoon place
    static bool createPath(const QString &path);
};
}
}

#endif // MERE_XDG_ICONTHEMEDIRECTORYSPEC_H
