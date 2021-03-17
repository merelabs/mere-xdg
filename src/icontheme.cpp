#include "icontheme.h"
#include <QVariant>

std::string Mere::XDG::IconTheme::id() const
{
    return get(Attribute::Id).toString().toStdString();
}

std::string Mere::XDG::IconTheme::name() const
{
    return get(Attribute::Name).toString().toStdString();
}

std::string Mere::XDG::IconTheme::comment() const
{
    return get(Attribute::Comment).toString().toStdString();
}

std::vector<std::string> Mere::XDG::IconTheme::directories() const
{
    std::vector<std::string> directories;

    QStringList list;

    QVariant value = get(Attribute::Directories);
    if(value.type() == QVariant::StringList)
        list = value.toStringList();
    else if(value.type() == QVariant::String)
        list = value.toString().split(", ");

    for(const auto &directory : list)
        directories.push_back(directory.toStdString());

    return directories;
}

std::vector<Mere::XDG::IconThemeSubDirectory> Mere::XDG::IconTheme::subdirectories() const
{
    return m_subdirectories;
}

void Mere::XDG::IconTheme::subdirectory(const IconThemeSubDirectory &sub)
{
    m_subdirectories.push_back(sub);
}

std::string Mere::XDG::IconTheme::path() const
{
    return m_path;
}

void Mere::XDG::IconTheme::path(const std::string &path)
{
    m_path = path;
}

bool Mere::XDG::IconTheme::hidden() const
{
    return get(Attribute::Hidden).toBool();
}

QVariant Mere::XDG::IconTheme::get(const Attribute &attribute) const
{
    auto find = m_attributes.find(attribute);
    if (find != m_attributes.end())
        return find->second;

    return QVariant();
}

void Mere::XDG::IconTheme::set(const Attribute &attribute, const QVariant &value)
{
    this->m_attributes.insert({attribute, value});
}

bool Mere::XDG::IconTheme::valid() const
{
    // Id is required
    QVariant id = get(Attribute::Id);
    if (!id.isValid()) return false;

    // Name is required
    QVariant name = get(Attribute::Name);
    if (!name.isValid()) return false;

    // Comment is required
    QVariant comment = get(Attribute::Comment);
    if (!comment.isValid()) return false;

    return true;
}
