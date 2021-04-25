#include "autostartdirectoryhelper.h"
#include "desktopentryhelper.h"
#include "autostartdirectory.h"

#include "mere/utils/binutils.h"
#include "mere/utils/stringutils.h"

#include <QDir>
std::vector<Mere::XDG::DesktopEntry> Mere::XDG::AutostartDirectoryHelper::applications()
{
    std::vector<DesktopEntry> desktopEntries ;

    std::vector<std::string>  directories = AutostartDirectory::directories();

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

            DesktopEntry desktopEntry = DesktopEntryHelper::parse(fileInfo);

            // ignore hidden application
            bool hidden = desktopEntry.hidden();
            if (hidden) continue;

            std::string onlyShowIn = desktopEntry.get(DesktopEntry::Attribute::OnlyShowIn);
            if (!onlyShowIn.empty())
            {
                QStringList list = QString(onlyShowIn.c_str()).split(":");
                if (!list.contains("MERE"))
                    continue;
            }

            std::string notShowIn = desktopEntry.get(DesktopEntry::Attribute::NotShowIn);
            if (!notShowIn.empty())
            {
                QStringList list = QString(notShowIn.c_str()).split(":");
                if (list.contains("MERE"))
                    continue;
            }

            std::string tryExec = desktopEntry.get(DesktopEntry::Attribute::TryExec);
            if (!tryExec.empty())
            {
                QFileInfo tryExecInfo(tryExec.c_str());
                if (!tryExecInfo.isAbsolute())
                {
                    std::string path = Mere::Utils::BinUtils::find(tryExecInfo.fileName().toStdString());
                    if (Mere::Utils::StringUtils::isBlank(path))
                        continue;
                }
                else if (!tryExecInfo.exists())
                {
                    continue;
                }
            }

            if (Mere::XDG::DesktopEntryHelper::valid(desktopEntry))
                desktopEntries.push_back(desktopEntry);
        }
    }

    return desktopEntries;
}
