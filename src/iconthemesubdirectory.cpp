#include "iconthemesubdirectory.h"

#include <QVariant>

std::string Mere::XDG::IconThemeSubDirectory::id() const
{
    return get(Attribute::Id).toString().toStdString();
}

std::string Mere::XDG::IconThemeSubDirectory::path() const
{
    return m_path;
}

void Mere::XDG::IconThemeSubDirectory::path(const std::string &path)
{
    m_path = path;
}

uint Mere::XDG::IconThemeSubDirectory::size() const
{
    return get(Attribute::Size).toUInt();
}

uint Mere::XDG::IconThemeSubDirectory::minsize() const
{
    return get(Attribute::MinSize).toUInt();
}

uint Mere::XDG::IconThemeSubDirectory::maxsize() const
{
    return get(Attribute::MaxSize).toUInt();
}

uint Mere::XDG::IconThemeSubDirectory::scale() const
{
    return get(Attribute::Scale).toUInt();
}

uint Mere::XDG::IconThemeSubDirectory::threshold() const
{
    return get(Attribute::Threshold).toUInt();
}

std::string Mere::XDG::IconThemeSubDirectory::type() const
{
    return get(Attribute::Type).toString().toStdString();
}

std::string Mere::XDG::IconThemeSubDirectory::context() const
{
    return get(Attribute::Context).toString().toStdString();
}

QVariant Mere::XDG::IconThemeSubDirectory::get(const Attribute &attribute) const
{
    auto find = m_attributes.find(attribute);
    if (find != m_attributes.end())
        return find->second;

    return QVariant();
}

void Mere::XDG::IconThemeSubDirectory::set(const Attribute &attribute, const QVariant &value)
{
    this->m_attributes.insert({attribute, value});
}

bool Mere::XDG::IconThemeSubDirectory::valid() const
{
    // Id is required
    QVariant id = get(Attribute::Id);
    if (!id.isValid()) return false;

    // Name is required
    QVariant size = get(Attribute::Size);
    if (!size.isValid()) return false;

    return true;
}
