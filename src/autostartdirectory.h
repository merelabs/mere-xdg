#ifndef MERE_XDG_AUTOSTARTDIRECTORYSPEC_H
#define MERE_XDG_AUTOSTARTDIRECTORYSPEC_H

#include "global.h"

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC AutostartDirectory
{
    AutostartDirectory() = default;
public:
    /**
     * @brief directories
     *
     * all directories where to search for desktop entry files, and will be
     * automatically launched during startup of the user's desktop environment
     * when the user has just logged in.
     *
     * @return
     */
    static std::vector<std::string> directories();


private:
    static const std::string AUTOSTART_DIRECTORY;

    static std::string directory(const std::string &path);

};

}
}

#endif // MERE_XDG_AUTOSTARTDIRECTORYSPEC_H
