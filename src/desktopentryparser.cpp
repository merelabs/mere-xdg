#include "desktopentryparser.h"
#include "desktopentrydirectory.h"

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

        std::string key   = this->key(line);
        std::string value = this->value(line);

        if (key.empty()) continue;

        if (key == "Type")
            m_entry.set(DesktopEntry::Attribute::Type, value.c_str());
        else if (key == "Version")
            m_entry.set(DesktopEntry::Attribute::Version, value.c_str());
        else if (key == "Name")
            m_entry.set(DesktopEntry::Attribute::Name, value.c_str());
        else if (key == "GenericName")
            m_entry.set(DesktopEntry::Attribute::GenericName, value.c_str());
        else if (key == "NoDisplay")
            m_entry.set(DesktopEntry::Attribute::NoDisplay, value.c_str());
        else if (key == "Comment")
            m_entry.set(DesktopEntry::Attribute::Comment, value.c_str());
        else if (key == "Icon")
            m_entry.set(DesktopEntry::Attribute::Icon, value.c_str());
        else if (key == "Hidden")
            m_entry.set(DesktopEntry::Attribute::Hidden, value.c_str());
        else if (key == "OnlyShowIn")
            m_entry.set(DesktopEntry::Attribute::OnlyShowIn, value.c_str());
        else if (key == "NotShowIn")
            m_entry.set(DesktopEntry::Attribute::NotShowIn, value.c_str());
        else if (key == "DBusActivatable")
            m_entry.set(DesktopEntry::Attribute::DBusActivatable, value.c_str());
        else if (key == "TryExec")
            m_entry.set(DesktopEntry::Attribute::TryExec, value.c_str());
        else if (key == "Exec")
            m_entry.set(DesktopEntry::Attribute::Exec, value.c_str());
        else if (key == "Path")
            m_entry.set(DesktopEntry::Attribute::Path, value.c_str());
        else if (key == "Terminal")
            m_entry.set(DesktopEntry::Attribute::Terminal, value.c_str());
        else if (key == "Actions")
            m_entry.set(DesktopEntry::Attribute::Actions, value.c_str());
        else if (key == "MimeType")
            m_entry.set(DesktopEntry::Attribute::MimeType, value.c_str());
        else if (key == "Categories")
        {
            m_entry.set(DesktopEntry::Attribute::Categories, value.c_str());

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

            m_entry.categories(categories);
        }
        else if (key == "Implements")
            m_entry.set(DesktopEntry::Attribute::Implements, value.c_str());
        else if (key == "Keywords")
            m_entry.set(DesktopEntry::Attribute::Keywords, value.c_str());
        else if (key == "StartupNotify")
            m_entry.set(DesktopEntry::Attribute::StartupNotify, value.c_str());
        else if (key == "StartupWMClass")
            m_entry.set(DesktopEntry::Attribute::StartupWMClass, value.c_str());
        else if (key == "URL")
            m_entry.set(DesktopEntry::Attribute::URL, value.c_str());
        else if (key == "PrefersNonDefaultGPU")
            m_entry.set(DesktopEntry::Attribute::PrefersNonDefaultGPU, value.c_str());
        else
            m_entry.set(key, value.c_str());
    }

    if (procceed)
    {
        for(const std::string &directory : Mere::XDG::DesktopEntryDirectory::directories())
        {
            auto pos = m_path.find(directory);
            if (pos != std::string::npos)
            {
                std::string id = m_path.substr(directory.length() + 1);
                pos = id.find("/");
                while(pos != std::string::npos)
                    id.replace(pos, 1, "-");
                m_entry.set(DesktopEntry::Attribute::Id, id.c_str());
                break;
            }
        }
    }

    return procceed;
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

