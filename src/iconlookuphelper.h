#ifndef MERE_XDG_ICONFINDER_H
#define MERE_XDG_ICONFINDER_H

#include "global.h"
#include "icontheme.h"

namespace Mere
{
namespace XDG
{

class IconLookupHelper
{
    IconLookupHelper() = default;
public:
    static std::string path(const std::string &icon);

private:
    static std::string LookupIcon(const std::string &icon);
    static std::string LookupIcon(const std::string &icon, const IconTheme &theme);

    static std::string LookupFallbackIcon(const std::string &icon);

    static bool DirectoryMatchesSize(const IconThemeSubDirectory &def, unsigned int size, unsigned int  scale);
    static int DirectorySizeDistance(const IconThemeSubDirectory &def, unsigned int size, unsigned int scale);

    static std::vector<std::string> filters(const std::string &icon);
    static std::string name(const std::string &icon);
};

}
}
#endif // MERE_XDG_ICONFINDER_H
