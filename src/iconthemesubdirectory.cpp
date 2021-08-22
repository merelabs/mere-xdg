#include "iconthemesubdirectory.h"

#include <QVariant>

std::string Mere::XDG::IconThemeSubDirectory::id() const
{
    return get(Attribute::Id);
}

std::string Mere::XDG::IconThemeSubDirectory::home() const
{
    return m_home;
}

void Mere::XDG::IconThemeSubDirectory::home(const std::string &home)
{
    m_home = home;
}

uint Mere::XDG::IconThemeSubDirectory::size() const
{
    bool set;
    std::string size = get(Attribute::Size, &set);

    if (!set || size.empty()) return 0;

    return std::stoi(size);
}

uint Mere::XDG::IconThemeSubDirectory::minsize() const
{
    bool set;
    std::string minsize = get(Attribute::MinSize, &set);

    if (!set || minsize.empty()) return 0;

    return std::stoi(minsize);
}

uint Mere::XDG::IconThemeSubDirectory::maxsize() const
{
    bool set;
    std::string maxsize = get(Attribute::MaxSize, &set);

    if (!set || maxsize.empty()) return 0;

    return std::stoi(maxsize);

}

uint Mere::XDG::IconThemeSubDirectory::scale() const
{
    bool set;
    std::string scale = get(Attribute::Scale, &set);

    if (!set || scale.empty()) return 0;

    return std::stoi(scale);
}

uint Mere::XDG::IconThemeSubDirectory::threshold() const
{
    bool set;
    std::string threshold = get(Attribute::Threshold, &set);

    if (!set || threshold.empty()) return 0;

    return std::stoi(threshold);

}

std::string Mere::XDG::IconThemeSubDirectory::type() const
{
    return get(Attribute::Type);
}

std::string Mere::XDG::IconThemeSubDirectory::context() const
{
    return get(Attribute::Context);
}

bool Mere::XDG::IconThemeSubDirectory::valid() const
{
    // Id is required
    std::string id = get(Attribute::Id);
    if (id.empty()) return false;

    // Name is required
    std::string size = get(Attribute::Size);
    if (!size.empty()) return false;

    return true;
}
