#include "desktopentrydirectoryhelper.h"
#include "desktopentrydirectory.h"
#include "desktopentryhelper.h"

#include <QDir>

std::vector<Mere::XDG::DesktopEntry> Mere::XDG::DesktopEntryDirectoryHelper::applicatins(const std::string &path, int offset, int number)
{
    QStringList filters;
    filters << "*.desktop";

    bool offsetHonored = false;

    int processed = 0;
    QFileInfoList files;

    std::vector<std::string>  directories = DesktopEntryDirectory::directories();
    for(const std::string &directory : directories)
    {
        if (!path.empty() && directory.compare(path)) continue;

        qDebug() << "Looking for apps into : " << directory.c_str();
        QDir dir(directory.c_str());

        QFileInfoList _files = dir.entryInfoList(filters, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        if (!_files.size()) continue;

        processed += _files.size();

        if (offset && !offsetHonored)
        {
            if (processed < offset) continue;

            int remove = _files.size() - (processed - offset);

            _files.erase(_files.begin(), _files.begin() + remove);

            processed -= remove;
            offsetHonored = true;
        }

        if (number)
        {
            if(processed - number > 0)
            {
                _files.erase(_files.begin() + (_files.size() - (processed - number)), _files.end());
                files.append(_files);
                break;
            }
        }

        files.append(_files);
    }

    std::vector<DesktopEntry> entries;
    for(const QFileInfo &file : files)
    {
        DesktopEntry desktopEntry = DesktopEntryHelper::parse(file);
        if (!desktopEntry.valid()) continue;
        entries.push_back(desktopEntry);
    }

    return entries;
}
