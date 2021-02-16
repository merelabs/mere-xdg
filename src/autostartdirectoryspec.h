#ifndef XDGAUTOSTARTDIRECTORYSPEC_H
#define XDGAUTOSTARTDIRECTORYSPEC_H

#include "global.h"
#include "desktopentry.h"

#include <vector>
#include <QList>

namespace Mere
{
namespace XDG
{

static const char* AUTOSTART_DIRECTORY = "autostart";

class MERE_XDG_LIB_SPEC AutostartDirectorySpec
{
private:
    AutostartDirectorySpec();
    static std::string autostarDirectory(const std::string  &path);
    static void expandEnvVars(QString &path);

public:
    /**
     * @brief autostartDirectories
     *
     * Directories when system will search for 'Desktop Entry' files, and will be
     * automatically launched during startup of the user's desktop environment after the user has logged in.
     *
     * @return
     */
    static std::vector<std::string> autostartDirectories();

    static std::vector<DesktopEntry> autostartApplications();
};

}
}

#endif // XDGAUTOSTARTDIRECTORYSPEC_H
