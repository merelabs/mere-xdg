#ifndef MERE_XDG_AUTOSTARTDIRECTORYSPEC_H
#define MERE_XDG_AUTOSTARTDIRECTORYSPEC_H

#include "global.h"
#include "desktopentry.h"

namespace Mere
{
namespace XDG
{

static const char* AUTOSTART_DIRECTORY = "autostart/";

class MERE_XDG_LIB_SPEC AutostartDirectory
{
    AutostartDirectory() = default;
public:
    /**
     * @brief directories
     *
     * Directories where system will search for 'Desktop Entry' files, and will be
     * automatically launched during startup of the user's desktop environment after the user has logged in.
     *
     * @return
     */
    static std::vector<std::string> directories();
    static std::vector<DesktopEntry> applications();

private:
    static std::string directory(const std::string &path);
};

}
}

#endif // MERE_XDG_AUTOSTARTDIRECTORYSPEC_H
