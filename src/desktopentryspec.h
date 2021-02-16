#ifndef MERE_XDG_DESKTOPENTRYSPEC_H
#define MERE_XDG_DESKTOPENTRYSPEC_H

#include "global.h"
#include "desktopentry.h"

#include <QFileInfo>

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC DesktopEntrySpec
{
private:
    DesktopEntrySpec();

public:
    static DesktopEntry parse(const QString &path);
    static DesktopEntry parse(const QFileInfo &fileInfo);
    static bool isValid(DesktopEntry &entry);
};
}
}

#endif // MERE_XDG_DESKTOPENTRYSPEC_H
