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
    return get(Attribute::Hidden).compare("false");
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

std::string Mere::XDG::DesktopEntry::get(const Attribute &attribute) const
{
    auto find = m_attributes.find(attribute);
    if (find != m_attributes.end())
        return find->second;

    return "";
}

void Mere::XDG::DesktopEntry::set(const Attribute &attribute, const std::string &value)
{
    this->m_attributes.insert({attribute, value});
}

std::string Mere::XDG::DesktopEntry::get(const std::string &attribute) const
{
    auto find = m_others.find(attribute);
    if (find != m_others.end())
        return find->second;

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
