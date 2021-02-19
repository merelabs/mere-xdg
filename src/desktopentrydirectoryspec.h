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
    DesktopEntryDirectorySpec() = default;
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

#endif // MERE_XDG_DESKTOPENTRYDIRECTORYSPEC_H
