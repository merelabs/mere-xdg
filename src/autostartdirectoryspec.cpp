#include "autostartdirectoryspec.h"
#include "basedirectoryspec.h"
#include "desktopentryspec.h"

#include "mere/utils/stringutils.h"

#include <QDir>
#include <QString>
#include <QStringList>
#include <QDirIterator>
#include <QDebug>

Mere::XDG::AutostartDirectorySpec::AutostartDirectorySpec()
{

}

std::vector<std::string> Mere::XDG::AutostartDirectorySpec::autostartDirectories()
{
    std::vector<std::string> autostartDirectories;

    QString userConfigHome = BaseDirectorySpec::userConfigDirectory();
    expandEnvVars(userConfigHome);

    if (Mere::Utils::StringUtils::isNotBlank(userConfigHome))
        autostartDirectories.push_back( autostarDirectory(userConfigHome.toStdString()) );

    const QStringList configSearchDirectories = BaseDirectorySpec::configSearchDirectories();
    for (QString configSearchDirectory : configSearchDirectories)
    {
        expandEnvVars(configSearchDirectory);

        if (Mere::Utils::StringUtils::isNotBlank(configSearchDirectory))
            autostartDirectories.push_back( autostarDirectory(configSearchDirectory.toStdString()) );
    }

    return autostartDirectories;
}

std::vector<Mere::XDG::DesktopEntry> Mere::XDG::AutostartDirectorySpec::autostartApplications()
{
    std::vector<DesktopEntry> desktopEntries ;

    std::vector<std::string>  autostartDirectories = AutostartDirectorySpec::autostartDirectories();

    for(const std::string &autostartDirectory : autostartDirectories)
    {
        QDir autostartDir(autostartDirectory.c_str());
        qDebug()<< "Looking for autostart apps in " << autostartDir;

        QFileInfoList fileInfoList = autostartDir.entryInfoList(QDir::AllEntries);
        QListIterator<QFileInfo> i(fileInfoList);
        while (i.hasNext())
        {
            QFileInfo fileInfo = i.next();

            if (fileInfo.isFile() && fileInfo.suffix() == "desktop")
            {
                DesktopEntry desktopEntry = DesktopEntrySpec::parse(fileInfo);

                if (Mere::XDG::DesktopEntrySpec::isValid(desktopEntry))
                    desktopEntries.push_back(desktopEntry);
            }
        }
    }

    return desktopEntries;
}

std::string Mere::XDG::AutostartDirectorySpec::autostarDirectory(const std::string &path)
{
    //FIXME
    QString autostartDirectory(path.c_str());

    if (autostartDirectory.endsWith(QDir::separator()))
        autostartDirectory = autostartDirectory.append(QString(XDG::AUTOSTART_DIRECTORY));
    else
        autostartDirectory = autostartDirectory.append(QString(QDir::separator()).append(QString(XDG::AUTOSTART_DIRECTORY)));

    return autostartDirectory.toStdString();
}

//FIXME
void Mere::XDG::AutostartDirectorySpec::expandEnvVars(QString &path)
{
    if (path.contains("$HOME"))
    {
        const QString home(getenv("HOME"));
        path = path.replace("$HOME", home);
    }

    if (path.contains("$USER"))
    {
        const QString user(getenv("USER"));
        path = path.replace("$USER", user);
    }
}
