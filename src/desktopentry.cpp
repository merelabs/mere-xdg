#include "desktopentry.h"

Mere::XDG::DesktopEntry::~DesktopEntry()
{

}

Mere::XDG::DesktopEntry::DesktopEntry()
{

}

Mere::XDG::DesktopEntry::DesktopEntry(const std::string &path)
{
    Q_UNUSED(path);
}

QVariant Mere::XDG::DesktopEntry::get(const Attribute &attribute)
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

bool Mere::XDG::DesktopEntry::valid()
{
    // Type is required
    QVariant type = get(DesktopEntry::Type);
    if (!type.isValid()) return false;

    // Name is required
    QVariant name = get(DesktopEntry::Name);
    if (!name.isValid()) return false;

    // URL is required for Link type
    if (type == QVariant("Link"))
    {
        QVariant url = get(DesktopEntry::URL);
        if (!url.isValid()) return false;
    }

    return true;
}
