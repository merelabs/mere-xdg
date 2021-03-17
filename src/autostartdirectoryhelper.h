#ifndef AUTOSTARTDIRECTORYHELPER_H
#define AUTOSTARTDIRECTORYHELPER_H

#include "desktopentry.h"

namespace Mere
{
namespace XDG
{

class AutostartDirectoryHelper
{
    AutostartDirectoryHelper() = default;
public:
    static std::vector<Mere::XDG::DesktopEntry> applications();

};

}
}

#endif // AUTOSTARTDIRECTORYHELPER_H
