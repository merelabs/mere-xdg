#include "desktopentryhelper.h"

#include "mere/utils/stringutils.h"

#include <iostream>
#include <QFile>
#include <QFileInfo>
#include <QSettings>

//static
Mere::XDG::DesktopEntry Mere::XDG::DesktopEntryHelper::parse(const QString &path)
{
    if(Mere::Utils::StringUtils::isBlank(path))
    {
        std::cout << "path can't be blank. please check the path." << std::endl;
        return DesktopEntry();
    }

    return parse(QFileInfo(path));
}

//static
Mere::XDG::DesktopEntry Mere::XDG::DesktopEntryHelper::parse(const std::string &path)
{
    if(Mere::Utils::StringUtils::isBlank(path))
    {
        std::cout << "path can't be blank. please check the path." << std::endl;
        return DesktopEntry();
    }

    return parse(QFileInfo(path.c_str()));
}

Mere::XDG::DesktopEntry Mere::XDG::DesktopEntryHelper::parse(const QFileInfo &fileInfo)
{
    if (!fileInfo.exists())
    {
        qDebug() << fileInfo.absoluteFilePath() << " does not exists. Please check the path.";
        return DesktopEntry();
    }

    DesktopEntry entry;

    // FIXME: transform path / to - after base directory
    entry.set(DesktopEntry::Attribute::Id, fileInfo.fileName());

    QSettings settings(fileInfo.absoluteFilePath(), QSettings::IniFormat);

    settings.beginGroup("Desktop Entry");
    const QStringList keys = settings.childKeys();
    for (const QString &key : keys)
    {
        QVariant value = settings.value(key);
        if (value.type() == QVariant::StringList)
            value = value.toStringList().join(", ");

        if (key == "Type")
            entry.set(DesktopEntry::Attribute::Type, value);
        else if (key == "Version")
            entry.set(DesktopEntry::Attribute::Version, value);
        else if (key == "Name")
            entry.set(DesktopEntry::Attribute::Name, value);
        else if (key == "GenericName")
            entry.set(DesktopEntry::Attribute::GenericName, value);
        else if (key == "NoDisplay")
            entry.set(DesktopEntry::Attribute::NoDisplay, value);
        else if (key == "Comment")
            entry.set(DesktopEntry::Attribute::Comment, value);
        else if (key == "Icon")
            entry.set(DesktopEntry::Attribute::Icon, value);
        else if (key == "Hidden")
            entry.set(DesktopEntry::Attribute::Hidden, value);
        else if (key == "OnlyShowIn")
            entry.set(DesktopEntry::Attribute::OnlyShowIn, value);
        else if (key == "NotShowIn")
            entry.set(DesktopEntry::Attribute::NotShowIn, value);
        else if (key == "DBusActivatable")
            entry.set(DesktopEntry::Attribute::DBusActivatable, value);
        else if (key == "TryExec")
            entry.set(DesktopEntry::Attribute::TryExec, value);
        else if (key == "Exec")
            entry.set(DesktopEntry::Attribute::Exec, value);
        else if (key == "Path")
            entry.set(DesktopEntry::Attribute::Path, value);
        else if (key == "Terminal")
            entry.set(DesktopEntry::Attribute::Terminal, value);
        else if (key == "Actions")
            entry.set(DesktopEntry::Attribute::Actions, value);
        else if (key == "MimeType")
            entry.set(DesktopEntry::Attribute::MimeType, value);
        else if (key == "Categories")
            entry.set(DesktopEntry::Attribute::Categories, value);
        else if (key == "Implements")
            entry.set(DesktopEntry::Attribute::Implements, value);
        else if (key == "Keywords")
            entry.set(DesktopEntry::Attribute::Keywords, value);
        else if (key == "StartupNotify")
            entry.set(DesktopEntry::Attribute::StartupNotify, value);
        else if (key == "StartupWMClass")
            entry.set(DesktopEntry::Attribute::StartupWMClass, value);
        else if (key == "URL")
            entry.set(DesktopEntry::Attribute::URL, value);
        else if (key == "PrefersNonDefaultGPU")
            entry.set(DesktopEntry::Attribute::PrefersNonDefaultGPU, value);
    }

    settings.endGroup();

    return entry;
}

bool Mere::XDG::DesktopEntryHelper::valid(DesktopEntry &entry)
{
    return entry.valid();
}
