#include "desktopentrydirectoryhelper.h"
#include "desktopentrydirectory.h"
#include "desktopentryhelper.h"

#include <QDir>

//static
std::vector<Mere::XDG::DesktopEntry> Mere::XDG::DesktopEntryDirectoryHelper::applicatins(const std::string &path)
{
    std::vector<DesktopEntry> entries;

    QStringList filters;
    filters << "*.desktop";

    std::vector<std::string>  directories = DesktopEntryDirectory::directories();

    for(const std::string &directory : directories)
    {
        qDebug() << "Looking for apps into : " << directory.c_str();
        QDir dir(directory.c_str());

        QFileInfoList files = dir.entryInfoList(filters, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        for(const QFileInfo &fileInfo : files)
        {
            DesktopEntry desktopEntry = DesktopEntryHelper::parse(fileInfo);

//            // ignore hidden application
//            QVariant hidden = desktopEntry.get(DesktopEntry::Attribute::Hidden);
//            if (!hidden.isNull() && hidden.isValid() && hidden.toBool())
//                continue;

//            QVariant onlyShowIn = desktopEntry.get(DesktopEntry::Attribute::OnlyShowIn);
//            if (!hidden.isNull() && onlyShowIn.isValid())
//            {
//                QStringList list = onlyShowIn.toString().split(":");
//                if (!list.contains("mere"))
//                    continue;
//            }

//            QVariant notShowIn = desktopEntry.get(DesktopEntry::Attribute::NotShowIn);
//            if (!hidden.isNull() && notShowIn.isValid())
//            {
//                QStringList list = notShowIn.toString().split(":");
//                if (list.contains("mere"))
//                    continue;
//            }

//            QVariant tryExec = desktopEntry.get(DesktopEntry::Attribute::TryExec);
//            if (!hidden.isNull() && tryExec.isValid())
//            {
//                QFileInfo tryExecInfo(tryExec.toString());
//                if (!tryExecInfo.isAbsolute())
//                {
//                    QString path = Mere::Utils::BinUtils::find(tryExecInfo.fileName());
//                    if (Mere::Utils::StringUtils::isBlank(path))
//                        continue;
//                }
//                else if (!tryExecInfo.exists())
//                {
//                    continue;
//                }
//            }

            if (desktopEntry.valid()) entries.push_back(desktopEntry);
        }
    }

    qDebug() << "KENO SESH HOCHHCE NA" << entries.size();
    return entries;
}
