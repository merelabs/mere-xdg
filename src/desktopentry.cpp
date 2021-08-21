#include "desktopentry.h"

std::string Mere::XDG::DesktopEntry::id() const
{
    return get(Attribute::Id);
}

std::string Mere::XDG::DesktopEntry::base() const
{
    std::string file = this->file();

    if (!file.empty())
    {
        auto pos = file.find_last_of("/");
        if (pos != std::string::npos)
            return file.substr(0, pos);
    }

    return "";
}

std::string Mere::XDG::DesktopEntry::type() const
{
    return get(Attribute::Type);
}

Mere::XDG::DesktopEntry::TypeId Mere::XDG::DesktopEntry::typeId() const
{
    if (type() == "Application")
        return Mere::XDG::DesktopEntry::TypeId::Application;

    if (type() == "Link")
        return Mere::XDG::DesktopEntry::TypeId::Link;

    if (type() == "Directory")
        return Mere::XDG::DesktopEntry::TypeId::Directory;

    return Mere::XDG::DesktopEntry::TypeId::Unknown;
}

std::string Mere::XDG::DesktopEntry::name() const
{
    return get(Attribute::Name);
}

std::string Mere::XDG::DesktopEntry::genericName() const
{
    return get(Attribute::GenericName);
}

std::string Mere::XDG::DesktopEntry::comment() const
{
    return get(Attribute::Comment);
}

std::string Mere::XDG::DesktopEntry::icon() const
{
    return get(Attribute::Icon);
}

bool Mere::XDG::DesktopEntry::hidden() const
{
    int set;
    std::string hidden = get(Attribute::Hidden, &set);

    if (!set) return false;

    return hidden.compare("true") == 0;
}

bool Mere::XDG::DesktopEntry::terminal() const
{
    int set;
    std::string terminal = get(Attribute::Terminal, &set);

    if (!set) return false;

    return terminal.compare("true") == 0;
}

bool Mere::XDG::DesktopEntry::nodisplay() const
{
    int set;
    std::string nodisplay = get(Attribute::NoDisplay, &set);

    if (!set) return false;

    return nodisplay.compare("true") == 0;
}

std::string Mere::XDG::DesktopEntry::exec() const
{
    return get(Attribute::Exec);
}

std::string Mere::XDG::DesktopEntry::path() const
{
    return get(Attribute::Path);
}

std::set<Mere::XDG::DesktopEntryAction> Mere::XDG::DesktopEntry::actions() const
{
    return m_actions;
}

void Mere::XDG::DesktopEntry::action(const DesktopEntryAction &action)
{
    m_actions.insert(action);
}

void Mere::XDG::DesktopEntry::actions(const std::set<DesktopEntryAction> &actions)
{
    m_actions.clear();
    m_actions = actions;
}

std::set<std::string> Mere::XDG::DesktopEntry::categories() const
{
    return m_categories;
}

void Mere::XDG::DesktopEntry::categories(const std::set<std::string> &categories)
{
    m_categories.clear();
    m_categories = categories;
}

bool Mere::XDG::DesktopEntry::valid() const
{
    // If the desktop file is not installed in an applications subdirectory of
    // one of the $XDG_DATA_DIRS components, it does not have an ID.
    // ref: https://specifications.freedesktop.org/desktop-entry-spec/desktop-entry-spec-latest.html
    //
    // So, the desktop file that is installed in xsessions subdirectory will not
    // have any id!!!
    // Id is required
    //std::string id = get(Attribute::Id);
    //if (id.empty()) return false;

    // Type is required
    std::string type = get(Attribute::Type);
    if (type.empty()) return false;

    // Name is required
    std::string name = get(Attribute::Name);
    if (name.empty()) return false;

    // URL is required for Link type
    if (type == "Link")
    {
        std::string url = get(Attribute::URL);
        if (url.empty()) return false;
    }

    // Exec is required
    std::string exec = get(Attribute::Exec);
    if (exec.empty()) return false;

    return true;
}
