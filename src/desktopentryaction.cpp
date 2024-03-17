#include "desktopentryaction.h"

Mere::XDG::DesktopEntryAction::DesktopEntryAction(const std::string &id)
{
    set(Attribute::Id, id);
}

std::string Mere::XDG::DesktopEntryAction::id() const
{
    return get(Attribute::Id);
}

std::string Mere::XDG::DesktopEntryAction::icon() const
{
    return get(Attribute::Icon);
}

std::string Mere::XDG::DesktopEntryAction::name() const
{
    return get(Attribute::Name);
}

std::string Mere::XDG::DesktopEntryAction::exec() const
{
    return get(Attribute::Exec);
}

std::string Mere::XDG::DesktopEntryAction::get(const Attribute &attribute, int *set) const
{
    if (auto find = m_attributes.find(attribute); find != m_attributes.end())
    {
        if (set) *set = 1;
        return find->second;
    }

    if (set) *set = 0;

    return "";
}

void Mere::XDG::DesktopEntryAction::set(const Attribute &attribute, const std::string &value)
{
    this->m_attributes.insert({attribute, value});
}

bool Mere::XDG::DesktopEntryAction::valid() const
{
    // Id is required
    std::string id = get(Attribute::Id);
    if (id.empty()) return false;

    // Name is required
    std::string name = get(Attribute::Name);
    if (name.empty()) return false;

    return true;
}
