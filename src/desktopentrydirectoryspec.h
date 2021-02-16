#ifndef MERE_XDG_DESKTOPENTRYDIRECTORYSPEC_H
#define MERE_XDG_DESKTOPENTRYDIRECTORYSPEC_H

#include "global.h"

namespace Mere
{
namespace XDG
{

static const char* APPLICATION_DIRECTORY = "applications";

class MERE_XDG_LIB_SPEC DesktopEntryDirectorySpec
{
public:
    DesktopEntryDirectorySpec();

public:
    /**
     * @brief applicationDirectories
     *
     * Directories where system will search for 'Desktop Entry' files.
     *
     * @return
     */
    static QStringList applicationDirectories();
    static QString applicationDirectory(const QString &path);

    // move it to a common place
    static void expandEnvVars(QString &path);
};
}
}

#endif // MERE_XDG_DESKTOPENTRYDIRECTORYSPEC_H
