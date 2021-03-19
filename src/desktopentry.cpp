#include "desktopentry.h"

std::string Mere::XDG::DesktopEntry::id() const
{
    return get(Attribute::Id);
}

std::string Mere::XDG::DesktopEntry::type() const
{
    return get(Attribute::Type);
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

std::string Mere::XDG::DesktopEntry::get(const Attribute &attribute, int *set) const
{
    auto find = m_attributes.find(attribute);
    if (find != m_attributes.end())
    {
        if (set) *set = 1;
        return find->second;
    }

    if (set) *set = 0;

    return "";
}

void Mere::XDG::DesktopEntry::set(const Attribute &attribute, const std::string &value)
{
    this->m_attributes.insert({attribute, value});
}

std::string Mere::XDG::DesktopEntry::get(const std::string &attribute, int *set) const
{
    auto find = m_others.find(attribute);
    if (find != m_others.end())
    {
        if (set) *set = 1;
        return find->second;
    }

    if (set) *set = 0;

    return "";
}

void Mere::XDG::DesktopEntry::set(const std::string &attribute, const std::string &value)
{
    this->m_others.insert({attribute, value});
}

bool Mere::XDG::DesktopEntry::valid() const
{
    // Id is required
    std::string id = get(Attribute::Id);
    if (id.empty()) return false;

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

    return true;
}
