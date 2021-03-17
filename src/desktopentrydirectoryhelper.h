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
    static std::vector<DesktopEntry> applicatins(const std::string &path = "");

};

}
}

#endif // DESKTOPENTRYDIRECTORYHELPER_H
