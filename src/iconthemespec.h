#ifndef MERE_XDG_ICONTHEMESPEC_H
#define MERE_XDG_ICONTHEMESPEC_H

#include "global.h"
#include "desktopentry.h"

namespace Mere
{
namespace XDG
{

typedef struct
{
    QString type;
    int scale;
    int size;
    int minsize;
    int maxsize;
    int threshold;
    QString context;
} IconDirectoryDefinition;

class MERE_XDG_LIB_SPEC IconThemeSpec
{
    IconThemeSpec() = default;
public:
    static std::string path(const std::string &icon);
    static std::string path(const std::string &icon, unsigned int size);
    static std::string path(const std::string &icon, unsigned int size, unsigned int scale);
    static std::string path(const std::string &icon, unsigned int size, unsigned int scale, const std::string &context);
    static std::string path(const DesktopEntry &entry);

private:
    static std::string FindIcon(const std::string &icon, unsigned int size, unsigned int  scale);
    static std::string FindIconHelper(const std::string &icon, unsigned int size, unsigned int scale, const std::string &theme);
    static std::string LookupIcon(const std::string &icon, unsigned int size, unsigned int  scale, const std::string &theme);
    static std::string LookupFallbackIcon(const std::string &icon);
    static bool DirectoryMatchesSize(const IconDirectoryDefinition &def, unsigned int size, unsigned int scale);
    static int DirectorySizeDistance(const IconDirectoryDefinition &def, unsigned int size, unsigned int scale);
};
}
}

#endif // MERE_XDG_ICONTHEMESPEC_H
