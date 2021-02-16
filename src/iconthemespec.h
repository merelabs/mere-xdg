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
public:
    ~IconThemeSpec();
    explicit IconThemeSpec();
    static QString path(const QString &icon);
    static QString path(const QString &icon, unsigned int size);
    static QString path(const QString &icon, unsigned int size, unsigned int scale);
    static QString path(const QString &icon, unsigned int size, unsigned int scale, const QString &context);
    static QString path(const DesktopEntry &entry);

private:
    static QString FindIcon(const QString &icon, unsigned int size, unsigned int  scale);
    static QString FindIconHelper(const QString &icon, unsigned int size, unsigned int scale, const QString &theme);
    static QString LookupIcon (const QString &icon, unsigned int size, unsigned int  scale, const QString &theme);
    static QString LookupFallbackIcon (const QString &icon);
    static bool DirectoryMatchesSize(const IconDirectoryDefinition &def, unsigned int size, unsigned int scale);
    static int DirectorySizeDistance(const IconDirectoryDefinition &def, unsigned int size, unsigned int scale);
};
}
}

#endif // MERE_XDG_ICONTHEMESPEC_H
