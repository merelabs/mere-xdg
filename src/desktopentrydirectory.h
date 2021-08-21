#ifndef MERE_XDG_DESKTOPENTRYDIRECTORY_H
#define MERE_XDG_DESKTOPENTRYDIRECTORY_H

#include "global.h"
#include "desktopentry.h"

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC DesktopEntryDirectory
{
    DesktopEntryDirectory() = default;
public:
    /**
     * @brief applicationDirectories
     *
     * all the directories where system will search for 'Desktop Entry' files.
     * note: all the directory path ends with '/'
     *
     * @return
     */
    static std::vector<std::string> directories();
    static std::string directory(const std::string &path);
};
}
}

#endif // MERE_XDG_DESKTOPENTRYDIRECTORY_H
