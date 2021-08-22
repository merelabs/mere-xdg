#include "desktopentryparser.h"
#include "desktopentrydirectory.h"

#include "mere/config/parser/gkparser.h"
#include "mere/utils/stringutils.h"

#include <set>
#include <fstream>
#include <iostream>

Mere::XDG::DesktopEntryParser::~DesktopEntryParser()
{

}

Mere::XDG::DesktopEntryParser::DesktopEntryParser(const std::string &path)
    : m_path(path)
{

}

Mere::XDG::DesktopEntry Mere::XDG::DesktopEntryParser::parse()
{
    DesktopEntry entry;

    Mere::Config::Spec::BaseEx config(m_path);

    config.group()->pattern("^\\[Desktop (Entry|Action).*\\]$");
    config.property()->pattern("^[^=]+=.*$");

    Mere::Config::Parser::GKParser parser(config);
    for(const auto &group : parser.parse())
    {
        std::vector<Mere::Config::Property *> properties = group->properties();

        if (properties.size() == 0) continue;

        if (group->name().compare("Desktop Entry") == 0)
        {
            for(const auto &property : properties)
            {
                DesktopEntry::Attribute attr = attribute(property->name());
                if (attr != DesktopEntry::Attribute::Others)
                {
                    entry.set(attr, property->value());
                    if (attr == DesktopEntry::Attribute::Categories)
                        entry.categories(categories(property->value()));
                }
                else
                {
                    entry.set(property->name(), property->value());
                }
            }
            entry.file(m_path);
            entry.set(DesktopEntry::Attribute::Id, id());
        }
        else if(group->name().find("Desktop Action") == 0)
        {
            DesktopEntryAction action;
            for(const auto &property : properties)
            {
                std::string key   = property->name();
                std::string value = property->value();
                if (key == "Name")
                    action.set(DesktopEntryAction::Attribute::Name, value);
                else if (key == "Icon")
                    action.set(DesktopEntryAction::Attribute::Icon, value);
                else if (key == "Exec")
                    action.set(DesktopEntryAction::Attribute::Exec, value);

            }
            entry.action(action);
        }
    }

    return entry;
}

std::string Mere::XDG::DesktopEntryParser::base() const
{
    std::string base;

    auto pos = m_path.find_last_of("/");
    if (pos != std::string::npos)
        base = m_path.substr(0, pos);

    return base;
}

std::set<std::string> Mere::XDG::DesktopEntryParser::categories(const std::string &value) const
{
    std::set<std::string> categories;

    std::string category;
    size_t start = 0, pos = value.find(";");
    while (pos != std::string::npos)
    {
        category = value.substr(start, pos - start);
        categories.insert(category);
        start = pos + 1;
        pos = value.find(";", start);
    }

    return categories;
}

Mere::XDG::DesktopEntry::Attribute Mere::XDG::DesktopEntryParser::attribute(const std::string &key) const
{
    DesktopEntry::Attribute attribute;

    if (key == "Type")
        attribute = DesktopEntry::Attribute::Type;
    else if (key == "Version")
        attribute = DesktopEntry::Attribute::Version;
    else if (key == "Name")
        attribute = DesktopEntry::Attribute::Name;
    else if (key == "GenericName")
        attribute = DesktopEntry::Attribute::GenericName;
    else if (key == "NoDisplay")
        attribute = DesktopEntry::Attribute::NoDisplay;
    else if (key == "Comment")
        attribute = DesktopEntry::Attribute::Comment;
    else if (key == "Icon")
        attribute = DesktopEntry::Attribute::Icon;
    else if (key == "Hidden")
        attribute = DesktopEntry::Attribute::Hidden;
    else if (key == "OnlyShowIn")
        attribute = DesktopEntry::Attribute::OnlyShowIn;
    else if (key == "NotShowIn")
        attribute = DesktopEntry::Attribute::NotShowIn;
    else if (key == "DBusActivatable")
        attribute = DesktopEntry::Attribute::DBusActivatable;
    else if (key == "TryExec")
        attribute = DesktopEntry::Attribute::TryExec;
    else if (key == "Exec")
        attribute = DesktopEntry::Attribute::Exec;
    else if (key == "Path")
        attribute = DesktopEntry::Attribute::Path;
    else if (key == "Terminal")
        attribute = DesktopEntry::Attribute::Terminal;
    else if (key == "Actions")
        attribute = DesktopEntry::Attribute::Actions;
    else if (key == "MimeType")
        attribute = DesktopEntry::Attribute::MimeType;
    else if (key == "Categories")
        attribute = DesktopEntry::Attribute::Categories;
    else if (key == "Implements")
        attribute = DesktopEntry::Attribute::Implements;
    else if (key == "Keywords")
        attribute = DesktopEntry::Attribute::Keywords;
    else if (key == "StartupNotify")
        attribute = DesktopEntry::Attribute::StartupNotify;
    else if (key == "StartupWMClass")
        attribute = DesktopEntry::Attribute::StartupWMClass;
    else if (key == "URL")
        attribute = DesktopEntry::Attribute::URL;
    else if (key == "PrefersNonDefaultGPU")
        attribute = DesktopEntry::Attribute::PrefersNonDefaultGPU;
    else
        attribute = DesktopEntry::Attribute::Others;

    return attribute;
}

std::string Mere::XDG::DesktopEntryParser::id() const
{
    std::string id;
    for(const std::string &directory : Mere::XDG::DesktopEntryDirectory::directories())
    {
        if (directory.empty()) continue;

        auto pos = m_path.find(directory);
        if (pos == std::string::npos) continue;
        id = m_path.substr(directory.length());
        while((pos = id.find("/")) != std::string::npos)
            id.replace(pos, 1, "-");
        break;
    }

    return id;
}

