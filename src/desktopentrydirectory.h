#ifndef MERE_XDG_DESKTOPENTRYDIRECTORY_H
#define MERE_XDG_DESKTOPENTRYDIRECTORY_H

#include "global.h"
#include "desktopentry.h"

namespace Mere
{
namespace XDG
{

static const char* APPLICATION_DIRECTORY = "applications";

class MERE_XDG_LIB_SPEC DesktopEntryDirectory
{
    DesktopEntryDirectory() = default;
public:
    /**
     * @brief applicationDirectories
     *
     * Directories where system will search for 'Desktop Entry' files.
     *
     * @return
     */
    static std::vector<std::string> directories();
    static std::string directory(const std::string &path);
};
}
}

#endif // MERE_XDG_DESKTOPENTRYDIRECTORY_H
