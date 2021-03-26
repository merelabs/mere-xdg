#include "desktopentrydirectoryhelper.h"
#include "desktopentrydirectory.h"
#include "desktopentryhelper.h"

#include <QDir>

std::map<std::string, std::vector<std::string>> Mere::XDG::DesktopEntryDirectoryHelper::g_paths = {};
std::vector<Mere::XDG::DesktopEntry> Mere::XDG::DesktopEntryDirectoryHelper::applicatins(const std::string &path, uint offset, uint number)
{
    std::vector<DesktopEntry> entries;

    std::vector<std::string> files = Mere::XDG::DesktopEntryDirectoryHelper::files(path);
    //qDebug() << "TOTAL FILES:" << files.size();
    if (!files.size()) return entries;

    if (offset)
    {
        if (offset >= files.size())
            files.clear();
        else
            files.erase(files.begin(), files.begin() + offset);
    }
    if (!files.size()) return entries;

    if (number && files.size() > number)
        files.erase(files.begin() + number, files.end());

    if (!files.size()) return entries;

    for(const std::string &file : files)
    {
        QFileInfo info(file.c_str());

        DesktopEntry desktopEntry = DesktopEntryHelper::parse(info);
        if (!desktopEntry.valid())
        {
            // dont we need to grab more files to fill this gap?
            continue;
        }
        entries.push_back(desktopEntry);
    }

    return entries;
}

//static
std::vector<std::string> Mere::XDG::DesktopEntryDirectoryHelper::files(const std::string &path)
{
    std::vector<std::string> files;

    QStringList filters{"*.desktop"};

    std::vector<std::string>  directories = DesktopEntryDirectory::directories();
    for(const std::string &directory : directories)
    {
        if (!path.empty() && directory.compare(path)) continue;

        auto it = g_paths.find(path);
        if (it != g_paths.end())
        {
            std::vector<std::string> paths = it->second;
            files.insert(files.end(), paths.begin(), paths.end());
            continue;
        }

        qDebug() << "Looking for apps into : " << directory.c_str();
        QDir dir(directory.c_str());

        dir.setSorting(QDir::IgnoreCase);

        QStringList list = dir.entryList(filters, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        if (!list.size()) continue;

        std::vector<std::string> paths;
        for(const QString &entry : list)
        {
            QString path(directory.c_str());
            path.append("/").append(entry);
            paths.push_back(path.toStdString());
        }

        files.insert(files.end(), paths.begin(), paths.end());
        g_paths.insert({path, paths});
    }

    return files;
}
