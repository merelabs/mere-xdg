#include "autostartdirectoryspec.h"
#include "basedirectoryspec.h"
#include "desktopentryspec.h"

#include "mere/utils/envutils.h"
#include "mere/utils/binutils.h"
#include "mere/utils/stringutils.h"

#include <QDir>
#include <QDirIterator>

std::vector<std::string> Mere::XDG::AutostartDirectorySpec::directories()
{
    std::vector<std::string> autostartDirectories;

    std::string userConfigHome = BaseDirectorySpec::configHome();
    Mere::Utils::EnvUtils::expandEnvVar(userConfigHome);

    if (Mere::Utils::StringUtils::isNotBlank(userConfigHome))
        autostartDirectories.push_back( Mere::XDG::AutostartDirectorySpec::directory(userConfigHome) );

    const std::vector<std::string> directories = BaseDirectorySpec::configDirectories();
    for (std::string directory : directories)
    {
        Mere::Utils::EnvUtils::expandEnvVar(directory);

        if (Mere::Utils::StringUtils::isNotBlank(directory))
            autostartDirectories.push_back( Mere::XDG::AutostartDirectorySpec::directory(directory) );
    }

    return autostartDirectories;
}

std::vector<Mere::XDG::DesktopEntry> Mere::XDG::AutostartDirectorySpec::applications()
{
    std::vector<DesktopEntry> desktopEntries ;

    std::vector<std::string>  directories = AutostartDirectorySpec::directories();

    for(const std::string &directory : directories)
    {
        QDir dir(directory.c_str());

        QFileInfoList fileInfoList = dir.entryInfoList(QDir::AllEntries);
        QListIterator<QFileInfo> i(fileInfoList);
        while (i.hasNext())
        {
            QFileInfo fileInfo = i.next();

            if (!fileInfo.isFile())
                continue;

            if (fileInfo.suffix() != "desktop")
                continue;

            DesktopEntry desktopEntry = DesktopEntrySpec::parse(fileInfo);

            // ignore hidden application
            QVariant hidden = desktopEntry.get(DesktopEntry::Hidden);
            if (!hidden.isNull() && hidden.isValid() && hidden.toBool())
                continue;

            QVariant onlyShowIn = desktopEntry.get(DesktopEntry::OnlyShowIn);
            if (!hidden.isNull() && onlyShowIn.isValid())
            {
                QStringList list = onlyShowIn.toString().split(":");
                if (!list.contains("mere"))
                    continue;
            }

            QVariant notShowIn = desktopEntry.get(DesktopEntry::NotShowIn);
            if (!hidden.isNull() && notShowIn.isValid())
            {
                QStringList list = notShowIn.toString().split(":");
                if (list.contains("mere"))
                    continue;
            }

            QVariant tryExec = desktopEntry.get(DesktopEntry::TryExec);
            if (!hidden.isNull() && tryExec.isValid())
            {
                QFileInfo tryExecInfo(tryExec.toString());
                if (!tryExecInfo.isAbsolute())
                {
                    QString path = Mere::Utils::BinUtils::find(tryExecInfo.fileName());
                    if (Mere::Utils::StringUtils::isBlank(path))
                        continue;
                }
                else if (!tryExecInfo.exists())
                {
                    continue;
                }
            }

            if (Mere::XDG::DesktopEntrySpec::valid(desktopEntry))
                desktopEntries.push_back(desktopEntry);
        }
    }

    return desktopEntries;
}

std::string Mere::XDG::AutostartDirectorySpec::directory(const std::string &path)
{
    std::string autostartDirectory(path);

    if (autostartDirectory[autostartDirectory.length() - 1] != '/')
        autostartDirectory.append("/");

    return autostartDirectory.append(XDG::AUTOSTART_DIRECTORY);
}
