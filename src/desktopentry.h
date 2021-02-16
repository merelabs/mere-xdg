#ifndef MERE_XDG_DESKTOPENTRY_H
#define MERE_XDG_DESKTOPENTRY_H

#include "global.h"

#include <QMap>
#include <QVariant>

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC DesktopEntry
{
public:
    ~DesktopEntry();
    explicit DesktopEntry();
    explicit DesktopEntry(QString &path);

    enum Attribute
    {
        DESKTOP_ENTRY_ID,
        DESKTOP_ENTRY_NAME,
        DESKTOP_ENTRY_ICON,
        DESKTOP_ENTRY_EXEC,
        DESKTOP_ENTRY_PATH,
        DESKTOP_ENTRY_URL,
        DESKTOP_ENTRY_COMMENT
    };

    QVariant  get(Attribute);
    void set(Attribute, QVariant value);

private:
    QMap<Attribute, QVariant> attributes;
};
}
}

#endif // MERE_XDG_DESKTOPENTRY_H
