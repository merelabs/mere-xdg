#include "icontheme.h"

#include <sstream>
#include <iostream>

std::string Mere::XDG::IconTheme::id() const
{
    return get(Attribute::Id);
}

std::string Mere::XDG::IconTheme::name() const
{
    return get(Attribute::Name);
}

std::string Mere::XDG::IconTheme::comment() const
{
    return get(Attribute::Comment);
}

std::vector<std::string> Mere::XDG::IconTheme::directories() const
{
    std::vector<std::string> directories;

    std::string value = get(Attribute::Directories);

    std::istringstream iss(value);
    for(std::string line; std::getline(iss, line, ',');)
        directories.push_back(line);

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

std::string Mere::XDG::IconTheme::home() const
{
    return m_home;
}

void Mere::XDG::IconTheme::home(const std::string &home)
{
    m_home = home;
}

bool Mere::XDG::IconTheme::hidden() const
{
    int set;
    std::string hidden = get(Attribute::Hidden, &set);

    if (!set) return false;

    return hidden.compare("true") == 0;
}

bool Mere::XDG::IconTheme::valid() const
{
    // Id is required
    std::string id = get(Attribute::Id);
    if (id.empty()) return false;

    // Name is required
    std::string name = get(Attribute::Name);
    if (name.empty()) return false;

    // Comment is required
    std::string comment = get(Attribute::Comment);
    if (comment.empty()) return false;

    return true;
}
