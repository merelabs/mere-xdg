#ifndef ICONFINDER_H
#define ICONFINDER_H

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


    static QStringList filters(const std::string &icon);
};

}
}
#endif // ICONFINDER_H