#include "iconthemeparser.h"
#include "iconthemedirectory.h"

#include "mere/config/parser/gkparser.h"
#include "mere/utils/stringutils.h"

Mere::XDG::IconThemeParser::~IconThemeParser()
{
}

Mere::XDG::IconThemeParser::IconThemeParser(const std::string &path)
    : m_path(path)
{
}

Mere::XDG::IconTheme Mere::XDG::IconThemeParser::parse()
{
    IconTheme m_theme;

    Mere::Config::Spec::BaseEx config(m_path);
    config.group()->pattern("^\\\[.+\\\]$");
    config.group()->delimiter("");

    Mere::Config::Parser::GKParser parser(config);

    m_theme.file(m_path);
    m_theme.set(IconTheme::Attribute::Id, id());

    auto pos = m_path.find_last_of("/");
    if (pos != std::string::npos)
        m_theme.home(m_path.substr(0, pos + 1));

    for(const auto& group : parser.parse())
    {
        if (group->name().compare("Icon Theme") == 0)
        {
            for(const auto& property : group->properties())
            {
                std::string key   = property->name();
                std::string value = property->value();

                IconTheme::Attribute attr = attribute(key);
                if (attr != IconTheme::Attribute::Others)
                    m_theme.set(attr, value);
                else
                    m_theme.set(key, value);
            }
            continue;
        }

        IconThemeSubDirectory subdir;
        subdir.set(IconThemeSubDirectory::Attribute::Id, group->name());
        subdir.home(m_theme.home());

        for(const auto& property : group->properties())
        {
            std::string key   = property->name();
            std::string value = property->value();

            IconThemeSubDirectory::Attribute attr = subattribute(key);
            if (attr != IconThemeSubDirectory::Attribute::Others)
                subdir.set(attr, value);
            else
                subdir.set(key, value);
        }

        m_theme.subdirectory(std::move(subdir));
    }

    return m_theme;
}

Mere::XDG::IconTheme::Attribute Mere::XDG::IconThemeParser::attribute(const std::string &key) const
{
    IconTheme::Attribute attribute;

    if (key == "Name")
        attribute = IconTheme::Attribute::Name;
    else if (key == "Comment")
        attribute = IconTheme::Attribute::Comment;
    else if (key == "Inherits")
        attribute = IconTheme::Attribute::Inherits;
    else if (key == "Directories")
        attribute = IconTheme::Attribute::Directories;
    else if (key == "ScaledDirectories")
        attribute = IconTheme::Attribute::ScaledDirectories;
    else if (key == "Hidden")
        attribute = IconTheme::Attribute::Hidden;
    else if (key == "Example")
        attribute = IconTheme::Attribute::Example;
    else
        attribute = IconTheme::Attribute::Others;

    return attribute;
}

Mere::XDG::IconThemeSubDirectory::Attribute Mere::XDG::IconThemeParser::subattribute(const std::string &key) const
{
    IconThemeSubDirectory::Attribute attribute;

    if (key == "Type")
        attribute = IconThemeSubDirectory::Attribute::Type;
    else if (key == "Context")
        attribute = IconThemeSubDirectory::Attribute::Context;
    else if (key == "Scale")
        attribute = IconThemeSubDirectory::Attribute::Scale;
    else if (key == "Size")
        attribute = IconThemeSubDirectory::Attribute::Size;
    else if (key == "MinSize")
        attribute = IconThemeSubDirectory::Attribute::MinSize;
    else if (key == "MaxSize")
        attribute = IconThemeSubDirectory::Attribute::MaxSize;
    else if (key == "Threshold")
        attribute = IconThemeSubDirectory::Attribute::Threshold;
    else
        attribute = IconThemeSubDirectory::Attribute::Others;

    return attribute;
}

std::string Mere::XDG::IconThemeParser::id() const
{
    std::string id;

    std::string path(m_path);
    for(const std::string &directory : Mere::XDG::IconThemeDirectory::directories())
    {
        if (directory.empty()) continue;

        auto pos = path.find(directory);
        if (pos == std::string::npos) continue;
        id = path.substr(directory.length());
        while((pos = id.find("/")) != std::string::npos)
            id.replace(pos, 1, "-");
        break;
    }

    return id;
}
