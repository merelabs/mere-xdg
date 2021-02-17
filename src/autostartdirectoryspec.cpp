#include "autostartdirectoryspec.h"
#include "basedirectoryspec.h"
#include "desktopentryspec.h"

#include "mere/utils/envutils.h"
#include "mere/utils/stringutils.h"

#include <QDir>
#include <QDirIterator>

std::vector<std::string> Mere::XDG::AutostartDirectorySpec::autostartDirectories()
{
    std::vector<std::string> autostartDirectories;

    std::string userConfigHome = BaseDirectorySpec::userConfigDirectory();
    Mere::Utils::EnvUtils::expandEnvVar(userConfigHome);

    if (Mere::Utils::StringUtils::isNotBlank(userConfigHome))
        autostartDirectories.push_back( autostarDirectory(userConfigHome) );

    const std::vector<std::string> configSearchDirectories = BaseDirectorySpec::configSearchDirectories();
    for (std::string configSearchDirectory : configSearchDirectories)
    {
        Mere::Utils::EnvUtils::expandEnvVar(configSearchDirectory);

        if (Mere::Utils::StringUtils::isNotBlank(configSearchDirectory))
            autostartDirectories.push_back( autostarDirectory(configSearchDirectory) );
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

        QFileInfoList fileInfoList = autostartDir.entryInfoList(QDir::AllEntries);
        QListIterator<QFileInfo> i(fileInfoList);
        while (i.hasNext())
        {
            QFileInfo fileInfo = i.next();

            if (fileInfo.isFile() && fileInfo.suffix() == "desktop")
            {
                DesktopEntry desktopEntry = DesktopEntrySpec::parse(fileInfo);

                if (Mere::XDG::DesktopEntrySpec::valid(desktopEntry))
                    desktopEntries.push_back(desktopEntry);
            }
        }
    }

    return desktopEntries;
}

std::string Mere::XDG::AutostartDirectorySpec::autostarDirectory(const std::string &path)
{
    std::string autostartDirectory(path);

    if (autostartDirectory[autostartDirectory.length() - 1] != '/')
        autostartDirectory.append("/");

    return autostartDirectory.append(XDG::AUTOSTART_DIRECTORY);
}
