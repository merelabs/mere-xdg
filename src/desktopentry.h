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
    DesktopEntry() = default;

    std::string id() const;
    std::string type() const;

    std::string name() const;
    std::string genericName() const;

    std::string comment() const;
    std::string icon() const;
    bool hidden() const;

    enum class Attribute
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

    QVariant  get(const Attribute &attribute) const;
    void set(const Attribute &attribute, const QVariant &value);

    bool valid() const;

private:
    std::map<Attribute, QVariant> m_attributes;
};

}
}

Q_DECLARE_METATYPE(Mere::XDG::DesktopEntry);

#endif // MERE_XDG_DESKTOPENTRY_H
