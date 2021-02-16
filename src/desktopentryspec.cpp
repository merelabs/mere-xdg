#include "desktopentryspec.h"

#include "mere/utils/stringutils.h"

#include <iostream>
#include <QFile>
#include <QFileInfo>
#include <QSettings>

//static
Mere::XDG::DesktopEntry Mere::XDG::DesktopEntrySpec::parse(const QString &path)
{
    if(Mere::Utils::StringUtils::isBlank(path))
    {
        std::cout << "path can't be blank. please check the path." << std::endl;
        return DesktopEntry();
    }

    return parse(QFileInfo(path));
}

Mere::XDG::DesktopEntry Mere::XDG::DesktopEntrySpec::parse(const QFileInfo &fileInfo)
{
    if (!fileInfo.exists())
    {
        qDebug() << fileInfo.absoluteFilePath() << " does not exists. Please check the path.";
        return DesktopEntry();
    }

    DesktopEntry entry;

    entry.set(DesktopEntry::Id, fileInfo.fileName());

    QSettings settings(fileInfo.absoluteFilePath(), QSettings::IniFormat);

    settings.beginGroup("Desktop Entry");
    const QStringList keys = settings.childKeys();
    for (const QString &key : keys)
    {
        QVariant value = settings.value(key);

        if (key == "Type")
            entry.set(DesktopEntry::Type, value);
        else if (key == "Version")
            entry.set(DesktopEntry::Version, value);
        else if (key == "Name")
            entry.set(DesktopEntry::Name, value);
        else if (key == "GenericName")
            entry.set(DesktopEntry::GenericName, value);
        else if (key == "NoDisplay")
            entry.set(DesktopEntry::NoDisplay, value);
        else if (key == "Comment")
            entry.set(DesktopEntry::Comment, value);
        else if (key == "Icon")
            entry.set(DesktopEntry::Icon, value);
        else if (key == "Hidden")
            entry.set(DesktopEntry::Hidden, value);
        else if (key == "OnlyShowIn")
            entry.set(DesktopEntry::OnlyShowIn, value);
        else if (key == "NotShowIn")
            entry.set(DesktopEntry::NotShowIn, value);
        else if (key == "DBusActivatable")
            entry.set(DesktopEntry::DBusActivatable, value);
        else if (key == "TryExec")
            entry.set(DesktopEntry::TryExec, value);
        else if (key == "Exec")
            entry.set(DesktopEntry::Exec, value);
        else if (key == "Path")
            entry.set(DesktopEntry::Path, value);
        else if (key == "Terminal")
            entry.set(DesktopEntry::Terminal, value);
        else if (key == "Actions")
            entry.set(DesktopEntry::Actions, value);
        else if (key == "MimeType")
            entry.set(DesktopEntry::MimeType, value);
        else if (key == "Categories")
            entry.set(DesktopEntry::Categories, value);
        else if (key == "Implements")
            entry.set(DesktopEntry::Implements, value);
        else if (key == "Keywords")
            entry.set(DesktopEntry::Keywords, value);
        else if (key == "StartupNotify")
            entry.set(DesktopEntry::StartupNotify, value);
        else if (key == "StartupWMClass")
            entry.set(DesktopEntry::StartupWMClass, value);
        else if (key == "URL")
            entry.set(DesktopEntry::URL, value);
        else if (key == "PrefersNonDefaultGPU")
            entry.set(DesktopEntry::PrefersNonDefaultGPU, value);
    }

    settings.endGroup();

    return entry;
}

bool Mere::XDG::DesktopEntrySpec::valid(DesktopEntry &entry)
{
    return entry.valid();
}
