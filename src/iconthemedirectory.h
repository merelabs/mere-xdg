#ifndef MERE_XDG_ICONTHEMEDIRECTORYSPEC_H
#define MERE_XDG_ICONTHEMEDIRECTORYSPEC_H

#include "global.h"

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC IconThemeDirectory
{
    IconThemeDirectory() = default;
public:
    static std::vector<std::string> directories();
    static std::vector<std::string> directories(const std::string &theme);

    static std::string home();

    /**
     * @brief iconDirectories
     *
     * Directories where system will search for icon theme files.
     *
     * @return
     */
    static std::vector<std::string> base();
    static std::vector<std::string> pixmaps();

    static std::string iconDirectory(const std::string &path);
};
}
}

#endif // MERE_XDG_ICONTHEMEDIRECTORYSPEC_H
