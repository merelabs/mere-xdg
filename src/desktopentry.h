#ifndef MERE_XDG_DESKTOPENTRY_H
#define MERE_XDG_DESKTOPENTRY_H

#include "global.h"
#include "desktopentryaction.h"

#include <map>
#include <set>

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
    bool terminal() const;
    bool nodisplay() const;

    std::string exec() const;
    std::string path() const;

    std::set<DesktopEntryAction> actions() const;
    void action(const DesktopEntryAction &action);
    void actions(const std::set<DesktopEntryAction> &actions);

    std::set<std::string> categories() const;
    void categories(const std::set<std::string> &categories);

    enum class Type
    {
        Unknown     = 0,
        Application = 1,
        Link        = 2,
        Directory   = 3
    };
    Type typeId() const;

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

    std::string get(const Attribute &attribute, int *set = nullptr) const;
    void set(const Attribute &attribute, const std::string &value);

    std::string  get(const std::string &key, int *set = nullptr) const;
    void set(const std::string &key, const std::string &value);

    bool valid() const;

private:
    std::map<Attribute, std::string> m_attributes;
    std::map<std::string, std::string> m_others;

    std::set<std::string> m_categories;
    std::set<DesktopEntryAction> m_actions;
};

}
}

Q_DECLARE_METATYPE(Mere::XDG::DesktopEntry);

#endif // MERE_XDG_DESKTOPENTRY_H
