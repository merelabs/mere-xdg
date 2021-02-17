#ifndef MERE_XDG_AUTOSTARTDIRECTORYSPEC_H
#define MERE_XDG_AUTOSTARTDIRECTORYSPEC_H

#include "global.h"
#include "desktopentry.h"

namespace Mere
{
namespace XDG
{

static const char* AUTOSTART_DIRECTORY = "autostart";

class MERE_XDG_LIB_SPEC AutostartDirectorySpec
{
    AutostartDirectorySpec() = default;
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

private:
    static std::string autostarDirectory(const std::string &path);
};

}
}

#endif // MERE_XDG_AUTOSTARTDIRECTORYSPEC_H
