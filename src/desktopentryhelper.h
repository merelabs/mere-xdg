#ifndef MERE_XDG_DESKTOPENTRYSPEC_H
#define MERE_XDG_DESKTOPENTRYSPEC_H

#include "global.h"
#include "desktopentry.h"

#include <QFileInfo>

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC DesktopEntryHelper
{
    DesktopEntryHelper() = default;
public:
    static DesktopEntry parse(const std::string &path);
    static DesktopEntry parse(const QFileInfo &fileInfo);
    static bool valid(DesktopEntry &entry);
};
}
}

#endif // MERE_XDG_DESKTOPENTRYSPEC_H
