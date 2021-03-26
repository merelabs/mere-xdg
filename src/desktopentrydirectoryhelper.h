#ifndef DESKTOPENTRYDIRECTORYHELPER_H
#define DESKTOPENTRYDIRECTORYHELPER_H

#include "global.h"
#include "desktopentry.h"

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC DesktopEntryDirectoryHelper
{
    DesktopEntryDirectoryHelper() = default;
public:
    static std::vector<DesktopEntry> applicatins(const std::string &path = "", uint offset = 0, uint number = 0);

private:
    static std::vector<std::string> files(const std::string &path = "");

    static std::map<std::string, std::vector<std::string>> g_paths;
};

}
}

#endif // DESKTOPENTRYDIRECTORYHELPER_H
