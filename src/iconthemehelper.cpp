#include "iconthemehelper.h"
#include "iconthemecontext.h"
#include "iconthemedirectory.h"
#include "iconthemesubdirectoryhelper.h"
#include "iconlookuphelper.h"

#include "desktopentry.h"

#include "mere/utils/stringutils.h"

#include <stdlib.h>
#include <iostream>

#include <QDir>
#include <QSettings>
#include <QDateTime>

//static
Mere::XDG::IconTheme Mere::XDG::IconThemeHelper::theme()
{
    // get the current theme name
    std::string name = "Adwaita";

    return IconThemeHelper::theme(name);
}

//static
Mere::XDG::IconTheme Mere::XDG::IconThemeHelper::theme(const std::string &name)
{
    IconTheme theme;

    std::vector<Mere::XDG::IconTheme> themes = IconThemeHelper::themes({{IconTheme::Attribute::Name, name.c_str()}});
    if (themes.size())
        theme = themes.at(0);

    return theme;
}

//static
std::vector<Mere::XDG::IconTheme> Mere::XDG::IconThemeHelper::themes(std::map<IconTheme::Attribute, QVariant> config)
{
    std::vector<Mere::XDG::IconTheme> themes;

    std::vector<std::string> dirs = IconThemeDirectory::base();
    for (const std::string &dir : dirs)
    {
        QDir d(dir.c_str());
        d.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
        for (const QFileInfo &info : d.entryInfoList())
        {
            QFileInfo themeInfo(info.absoluteFilePath().append("/index.theme"));
            if (!themeInfo.exists()) continue;

            IconTheme theme = IconThemeHelper::parse(themeInfo);
            if (!theme.valid()) continue;

            // filter on name
            QVariant name = config[IconTheme::Attribute::Name];
            if (name.isValid() && theme.name().compare(name.toString().toStdString()))
                continue;

            // filter on hidden
            QVariant hidden = config[IconTheme::Attribute::Hidden];
            if (hidden.isValid() && theme.hidden() != hidden.toBool())
                continue;

            theme.path(info.absoluteFilePath().toStdString());
            themes.push_back(theme);
        }
    }

    qDebug() << "Number of themes: " << themes.size();
    return themes;
}

//static
std::string Mere::XDG::IconThemeHelper::icon(const DesktopEntry &entry)
{
    if (!entry.valid()) return "";

    std::string path = IconLookupHelper::path(entry.icon());
    if(path.empty())
    {
        // FIXME: if no icon found????
        path = IconLookupHelper::path("applications-accessories");
    }

    return path;
}

//static
Mere::XDG::IconTheme Mere::XDG::IconThemeHelper::parse(const QString &path)
{
    if(Mere::Utils::StringUtils::isBlank(path))
    {
        std::cout << "path can't be blank. please check the path." << std::endl;
        return IconTheme();
    }

    return parse(QFileInfo(path));
}

//static
Mere::XDG::IconTheme Mere::XDG::IconThemeHelper::parse(const std::string &path)
{
    if(Mere::Utils::StringUtils::isBlank(path))
    {
        std::cout << "path can't be blank. please check the path." << std::endl;
        return IconTheme();
    }

    return parse(QFileInfo(path.c_str()));
}

Mere::XDG::IconTheme Mere::XDG::IconThemeHelper::parse(const QFileInfo &fileInfo)
{
    if (!fileInfo.exists())
    {
        qDebug() << fileInfo.absoluteFilePath() << " does not exists. Please check the path.";
        return IconTheme();
    }

    IconTheme entry;

    // FIXME: transform path / to - after base directory
    entry.set(IconTheme::Attribute::Id, fileInfo.fileName());

    QSettings settings(fileInfo.absoluteFilePath(), QSettings::IniFormat);

    settings.beginGroup("Icon Theme");
    const QStringList keys = settings.childKeys();
    for (const QString &key : keys)
    {
        QVariant value = settings.value(key);
        if (value.type() == QVariant::StringList)
            value = value.toStringList().join(", ");

        if (key == "Name")
            entry.set(IconTheme::Attribute::Name, value);
        else if (key == "Comment")
            entry.set(IconTheme::Attribute::Comment, value);
        else if (key == "Inherits")
            entry.set(IconTheme::Attribute::Inherits, value);
        else if (key == "Directories")
            entry.set(IconTheme::Attribute::Directories, value);
        else if (key == "ScaledDirectories")
            entry.set(IconTheme::Attribute::ScaledDirectories, value);
        else if (key == "Hidden")
            entry.set(IconTheme::Attribute::Hidden, value);
        else if (key == "Example")
            entry.set(IconTheme::Attribute::Example, value);
    }

    settings.endGroup();

    for(const std::string &directory : entry.directories())
    {
        IconThemeSubDirectory sub = IconThemeSubDirectoryHelper::parse(fileInfo, directory);
        if (sub.valid()) entry.subdirectory(sub);
    }

    return entry;
}

bool Mere::XDG::IconThemeHelper::valid(IconTheme &theme)
{
    return theme.valid();
}
