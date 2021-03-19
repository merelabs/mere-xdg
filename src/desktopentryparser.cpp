#include "desktopentryparser.h"
#include "desktopentrydirectory.h"

#include <set>
#include <fstream>
#include <iostream>

Mere::XDG::DesktopEntryParser::~DesktopEntryParser()
{

}

Mere::XDG::DesktopEntryParser::DesktopEntryParser(const std::string &path, QObject *parent)
    : QObject(parent),
      m_path(path)
{

}

Mere::XDG::DesktopEntry Mere::XDG::DesktopEntryParser::entry() const
{
    return m_entry;
}

bool Mere::XDG::DesktopEntryParser::parse()
{
    if (m_path.empty()) return false;

    // check for the file extension
    std::string ext(".desktop");
    auto pos = m_path.find(ext);
    if (pos != m_path.length() - ext.length())
        return false;

    std::ifstream file(m_path);

    // check for the file existance
    if (!file.good()) return false;

    bool procceed = false;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        if (this->comment(line)) continue;

        if (!line.compare("[Desktop Entry]"))
        {
            procceed = true;
            continue;
        }

        if (!procceed) continue;

        auto pos = line.find("[Desktop Action");
        if (pos != std::string::npos)
        {
            std::set<DesktopEntryAction> actions = Mere::XDG::DesktopEntryParser::actions(file, line);
            m_entry.actions(actions);
            continue;
        }

        std::string key   = this->key(line);
        std::string value = this->value(line);

        if (key.empty()) continue;

        if (key == "Type")
            m_entry.set(DesktopEntry::Attribute::Type, value);
        else if (key == "Version")
            m_entry.set(DesktopEntry::Attribute::Version, value);
        else if (key == "Name")
            m_entry.set(DesktopEntry::Attribute::Name, value);
        else if (key == "GenericName")
            m_entry.set(DesktopEntry::Attribute::GenericName, value);
        else if (key == "NoDisplay")
            m_entry.set(DesktopEntry::Attribute::NoDisplay, value);
        else if (key == "Comment")
            m_entry.set(DesktopEntry::Attribute::Comment, value);
        else if (key == "Icon")
            m_entry.set(DesktopEntry::Attribute::Icon, value);
        else if (key == "Hidden")            
            m_entry.set(DesktopEntry::Attribute::Hidden, value);
        else if (key == "OnlyShowIn")
            m_entry.set(DesktopEntry::Attribute::OnlyShowIn, value);
        else if (key == "NotShowIn")
            m_entry.set(DesktopEntry::Attribute::NotShowIn, value);
        else if (key == "DBusActivatable")
            m_entry.set(DesktopEntry::Attribute::DBusActivatable, value);
        else if (key == "TryExec")
            m_entry.set(DesktopEntry::Attribute::TryExec, value);
        else if (key == "Exec")
            m_entry.set(DesktopEntry::Attribute::Exec, value);
        else if (key == "Path")
            m_entry.set(DesktopEntry::Attribute::Path, value);
        else if (key == "Terminal")
            m_entry.set(DesktopEntry::Attribute::Terminal, value);
        else if (key == "Actions")
            m_entry.set(DesktopEntry::Attribute::Actions, value);
        else if (key == "MimeType")
            m_entry.set(DesktopEntry::Attribute::MimeType, value);
        else if (key == "Categories")
        {
            m_entry.set(DesktopEntry::Attribute::Categories, value);
            m_entry.categories(categories(value));
        }
        else if (key == "Implements")
            m_entry.set(DesktopEntry::Attribute::Implements, value);
        else if (key == "Keywords")
            m_entry.set(DesktopEntry::Attribute::Keywords, value);
        else if (key == "StartupNotify")
            m_entry.set(DesktopEntry::Attribute::StartupNotify, value);
        else if (key == "StartupWMClass")
            m_entry.set(DesktopEntry::Attribute::StartupWMClass, value);
        else if (key == "URL")
            m_entry.set(DesktopEntry::Attribute::URL, value);
        else if (key == "PrefersNonDefaultGPU")
            m_entry.set(DesktopEntry::Attribute::PrefersNonDefaultGPU, value);
        else
            m_entry.set(key, value.c_str());
    }


    m_entry.set(DesktopEntry::Attribute::Id, id());

    return procceed;
}

std::string Mere::XDG::DesktopEntryParser::id() const
{
    std::string id;
    for(const std::string &directory : Mere::XDG::DesktopEntryDirectory::directories())
    {
        if (directory.empty()) continue;

        auto pos = m_path.find(directory);
        if (pos == std::string::npos) continue;

        id = m_path.substr(directory.length() + 1);
        while((pos = id.find("/"))!= std::string::npos)
            id.replace(pos, 1, "-");
        break;
    }

    return id;
}

bool Mere::XDG::DesktopEntryParser::comment(const std::string &line) const
{
    auto pos = line.find("#");

    return pos == 0;
}

std::string Mere::XDG::DesktopEntryParser::key(const std::string &line) const
{
    auto pos = line.find("=");
    if (pos == 0 || pos == std::string::npos) return "";

    return line.substr(0, pos);
}

std::string Mere::XDG::DesktopEntryParser::value(const std::string &line) const
{
    auto pos = line.find("=");
    if (pos == 0 || pos == std::string::npos) return "";

    return line.substr(pos + 1);
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

std::set<Mere::XDG::DesktopEntryAction> Mere::XDG::DesktopEntryParser::actions(std::ifstream &file, std::string &line) const
{
    std::set<Mere::XDG::DesktopEntryAction> actions;

    std::string id = line.substr(16);

    DesktopEntryAction action(id);

    while (std::getline(file, line))
    {
        auto pos = line.find("[Desktop Action");
        if (pos != std::string::npos)
        {
            std::set<Mere::XDG::DesktopEntryAction> _actions = Mere::XDG::DesktopEntryParser::actions(file, line);
            actions.insert(_actions.begin(), _actions.end());
        }

        std::string key   = this->key(line);
        std::string value = this->value(line);

        if (key == "Name")
            action.set(DesktopEntryAction::Attribute::Name, value);
        else if (key == "Icon")
            action.set(DesktopEntryAction::Attribute::Icon, value);
        else if (key == "Exec")
            action.set(DesktopEntryAction::Attribute::Exec, value);
    }

    if (action.valid())
        actions.insert(action);

    return actions;
}

