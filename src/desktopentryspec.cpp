#include "desktopentryspec.h"

#include "mere/utils/stringutils.h"

#include <QFile>
#include <QFileInfo>
#include <QSettings>

Mere::XDG::DesktopEntrySpec::DesktopEntrySpec()
{

}

Mere::XDG::DesktopEntry Mere::XDG::DesktopEntrySpec::parse(const QString &path)
{
    if(Mere::Utils::StringUtils::isBlank(path))
    {
        qDebug() << path << " can't be blank. Please check the path.";
        return DesktopEntry();
    }


    qDebug() << "Going to read .desktop file";
    DesktopEntry entry;

    QSettings settings(path, QSettings::IniFormat);
    settings.beginGroup("Desktop Entry");
    const QStringList keys = settings.childKeys();
    foreach (const QString &key, keys)
    {
        QVariant value = settings.value(key);

        if (key == "Name")
            entry.set(DesktopEntry::DESKTOP_ENTRY_NAME, value);
        else if (key == "Icon")
            entry.set(DesktopEntry::DESKTOP_ENTRY_ICON, value);
        else if (key == "Exec")
            entry.set(DesktopEntry::DESKTOP_ENTRY_EXEC, value);
        else if (key == "Path")
            entry.set(DesktopEntry::DESKTOP_ENTRY_PATH, value);
        else if (key == "URL")
            entry.set(DesktopEntry::DESKTOP_ENTRY_URL, value);
        else if (key == "Comment")
            entry.set(DesktopEntry::DESKTOP_ENTRY_COMMENT, value);

        //qDebug() << key << value;
    }

    settings.endGroup();

    return entry;
}

Mere::XDG::DesktopEntry Mere::XDG::DesktopEntrySpec::parse(const QFileInfo &fileInfo)
{
    if (!fileInfo.exists())
    {
        qDebug() << fileInfo.absoluteFilePath() << " does not exists. Please check the path.";
        return DesktopEntry();
    }

//    if(!fileInfo.isReadable())
//    {
//        qDebug() << fileInfo.absoluteFilePath() << " is not readable. Please check the path.";
//        return NULL;
//    }

    return parse(fileInfo.absoluteFilePath());
}

//FIXME
bool Mere::XDG::DesktopEntrySpec::isValid(DesktopEntry &entry)
{
    Q_UNUSED(entry);

    return true;
}
