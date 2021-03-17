#ifndef MERE_XDG_ICONTHEMESPEC_H
#define MERE_XDG_ICONTHEMESPEC_H

#include "global.h"
#include "icontheme.h"
#include "desktopentry.h"

#include <QFileInfo>
#include <QSettings>

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC IconThemeHelper
{
    IconThemeHelper() = default;
public:
    static IconTheme theme();
    static IconTheme theme(const std::string &name);
    static std::vector<IconTheme> themes(std::map<IconTheme::Attribute, QVariant> config = {});

    static std::string icon(const DesktopEntry &entry);

    static IconTheme parse(const QString &path);
    static IconTheme parse(const std::string &path);
    static IconTheme parse(const QFileInfo &fileInfo);
    static bool valid(IconTheme &theme);
};
}
}

#endif // MERE_XDG_ICONTHEMESPEC_H
