#ifndef MERE_XDG_DESKTOPENTRY_H
#define MERE_XDG_DESKTOPENTRY_H

#include "global.h"
#include "baseentry.h"
#include "desktopentryaction.h"

#include <map>
#include <set>

namespace Mere::XDG
{

class MERE_XDG_LIB_SPEC DesktopEntry : public BaseEntry
{
public:
    ~DesktopEntry() = default;
    DesktopEntry() = default;

    DesktopEntry(const DesktopEntry &that) = default;
    DesktopEntry& operator=(const DesktopEntry &that) = default;

    DesktopEntry(DesktopEntry &&that) = default ;
    DesktopEntry& operator=(DesktopEntry &&that) = default;

    std::string id() const;
    std::string base() const;

    std::string type() const;

    std::string name() const;
    std::string genericName() const;

    std::string comment() const;
    std::string icon() const;

    bool hidden() const;
    bool terminal() const;
    bool nodisplay() const;

    std::string exec() const;
    std::string path() const;

    std::set<DesktopEntryAction> actions() const;
    void action(const DesktopEntryAction &action);
    void actions(const std::set<DesktopEntryAction> &actions);

    std::set<std::string> categories() const;
    void categories(const std::set<std::string> &categories);

    enum class TypeId
    {
        Unknown     = 0,
        Application = 1,
        Link        = 2,
        Directory   = 3
    };
    TypeId typeId() const;

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
        PrefersNonDefaultGPU,
        Others
    };


    bool valid() const;

private:

    std::set<std::string> m_categories{};
    std::set<DesktopEntryAction> m_actions{};
};

}


Q_DECLARE_METATYPE(Mere::XDG::DesktopEntry);

#endif // MERE_XDG_DESKTOPENTRY_H
