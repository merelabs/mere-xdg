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
    IconThemeDirectorySpec() = default;
public:

    static std::string userIconDirectory();

    /**
     * @brief iconDirectories
     *
     * Directories where system will search for icon theme files.
     *
     * @return
     */
    static std::vector<std::string> baseDirectories();
    static std::string iconDirectory(const std::string &path);

    static std::vector<std::string> themeDirectories(const std::string &theme);
};
}
}

#endif // MERE_XDG_ICONTHEMEDIRECTORYSPEC_H
