#include "desktopentry.h"

std::string Mere::XDG::DesktopEntry::id() const
{
    return get(Attribute::Id).toString().toStdString();
}

std::string Mere::XDG::DesktopEntry::type() const
{
    return get(Attribute::Type).toString().toStdString();
}

std::string Mere::XDG::DesktopEntry::name() const
{
    return get(Attribute::Name).toString().toStdString();
}

std::string Mere::XDG::DesktopEntry::genericName() const
{
    return get(Attribute::GenericName).toString().toStdString();
}

std::string Mere::XDG::DesktopEntry::comment() const
{
    return get(Attribute::Comment).toString().toStdString();
}

std::string Mere::XDG::DesktopEntry::icon() const
{
    return get(Attribute::Icon).toString().toStdString();
}

bool Mere::XDG::DesktopEntry::hidden() const
{
    return get(Attribute::Hidden).toBool();
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

QVariant Mere::XDG::DesktopEntry::get(const Attribute &attribute) const
{
    auto find = m_attributes.find(attribute);
    if (find != m_attributes.end())
        return find->second;

    return QVariant();
}

void Mere::XDG::DesktopEntry::set(const Attribute &attribute, const QVariant &value)
{
    this->m_attributes.insert({attribute, value});
}

QVariant Mere::XDG::DesktopEntry::get(const std::string &attribute) const
{
    auto find = m_others.find(attribute);
    if (find != m_others.end())
        return find->second;

    return QVariant();
}

void Mere::XDG::DesktopEntry::set(const std::string &attribute, const QVariant &value)
{
    this->m_others.insert({attribute, value});
}

bool Mere::XDG::DesktopEntry::valid() const
{
    // Id is required
    QVariant id = get(Attribute::Id);
    if (!id.isValid()) return false;

    // Type is required
    QVariant type = get(Attribute::Type);
    if (!type.isValid()) return false;

    // Name is required
    QVariant name = get(Attribute::Name);
    if (!name.isValid()) return false;

    // URL is required for Link type
    if (type == QVariant("Link"))
    {
        QVariant url = get(Attribute::URL);
        if (!url.isValid()) return false;
    }

    return true;
}
