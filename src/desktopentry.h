#ifndef MERE_XDG_DESKTOPENTRY_H
#define MERE_XDG_DESKTOPENTRY_H

#include "global.h"
#include <map>

#include <QVariant>

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC DesktopEntry
{
public:
    ~DesktopEntry();
    DesktopEntry();

    explicit DesktopEntry(const std::string &path);

    enum Attribute
    {
        Id,
        Type,
        Version,
        Name,
        GenericName,
        NoDisplay,
        Comment,
        Icon,
        Hidden,
        OnlyShowIn,
        NotShowIn,
        DBusActivatable,
        TryExec,
        Exec,
        Path,
        Terminal,
        Actions,
        MimeType,
        Categories,
        Implements,
        Keywords,
        StartupNotify,
        StartupWMClass,
        URL,
        PrefersNonDefaultGPU
    };

    QVariant  get(const Attribute &attribute);
    void set(const Attribute &attribute, const QVariant &value);

    bool valid();

private:
    std::map<Attribute, QVariant> m_attributes;
};
}
}

#endif // MERE_XDG_DESKTOPENTRY_H
