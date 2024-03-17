#include "desktopentrydirectorytraverser.h"
#include "desktopentrydirectory.h"
#include "desktopentryparser.h"

#include <sys/types.h>
#include <dirent.h>
#include <future>

Mere::XDG::DesktopEntryDirectoryTraverser::DesktopEntryDirectoryTraverser(QObject *parent)
    : QObject(parent)
{

}

std::vector<Mere::XDG::DesktopEntry> Mere::XDG::DesktopEntryDirectoryTraverser::traverse() const
{
    std::vector<Mere::XDG::DesktopEntry> entries;

    for(const std::string &directory : DesktopEntryDirectory::directories())
    {
        if (const auto &_entries = this->traverse(directory); !_entries.empty())
        {
            entries.insert(entries.end(), std::make_move_iterator(_entries.begin()), std::make_move_iterator(_entries.end()));
        }
    }

    return entries;
}

std::vector<Mere::XDG::DesktopEntry> Mere::XDG::DesktopEntryDirectoryTraverser::traverse(DesktopEntry::TypeId type) const
{
    std::vector<Mere::XDG::DesktopEntry> entries;

    for(const std::string &directory : DesktopEntryDirectory::directories())
    {
        if (std::vector<Mere::XDG::DesktopEntry> _entries = this->traverse(directory, type); !_entries.empty())
        {
            entries.insert(entries.end(), std::make_move_iterator(_entries.begin()), std::make_move_iterator(_entries.end()));
        }
    }

    return entries;
}

std::vector<Mere::XDG::DesktopEntry> Mere::XDG::DesktopEntryDirectoryTraverser::traverse(const std::string &path) const
{
    std::vector<Mere::XDG::DesktopEntry> entries;

    std::string base(path);

    std::vector<std::string> files = this->files(path);
    for(const std::string &file : files)
    {
        std::string p(base);

        DesktopEntryParser parser(p.append(file));
        DesktopEntry entry = parser.parse();
        if(!entry.valid()) continue;

        entries.push_back(std::move(entry));
    }

    emit traversed(path);

    return entries;
}

std::vector<Mere::XDG::DesktopEntry> Mere::XDG::DesktopEntryDirectoryTraverser::traverse(const std::string &path, DesktopEntry::TypeId type) const
{
    std::map<std::string, std::future<DesktopEntry>> tasks;

    std::vector<std::string> files = this->files(path);
    for(const std::string &file : files)
    {
         auto future = std::async(std::launch::async, [&](const std::string &path, const std::string &file) -> DesktopEntry {
             std::string p(path);
             DesktopEntryParser parser(p.append(file));
             return parser.parse();
         }, path, file);

         tasks.insert(std::make_pair(file, std::move(future)));
    }

    // can we process it in two phase?
    // checking done condition?
    // task.finish?

    std::vector<Mere::XDG::DesktopEntry> entries;
    for(auto &task : tasks)
    {
        DesktopEntry entry = task.second.get();
        if(!entry.valid()) continue;
        if (entry.typeId() != type) continue;
        entries.push_back(std::move(entry));
    }

    //emit traversed(path);

    return entries;
}

std::map<std::string, std::vector<std::string>> Mere::XDG::DesktopEntryDirectoryTraverser::files() const
{
    std::map<std::string, std::vector<std::string>> files;

    std::vector<std::string> directoris = Mere::XDG::DesktopEntryDirectory::directories();
    for(const std::string &directory : directoris)
    {
        std::vector<std::string> _files = this->files(directory);
        if (_files.empty()) continue;

        files.insert({directory, std::move(_files)});
    }

    return files;
}

std::vector<std::string> Mere::XDG::DesktopEntryDirectoryTraverser::files(const std::string &path) const
{
    std::vector<std::string> files;

    if (path.empty()) return files;

    if (DIR *dir = opendir(path.c_str()))
    {
        const char *extension = ".desktop";

        struct dirent *dp;
        while ((dp = readdir(dir)))
        {
            //if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0 )
            //    continue;

            if (strlen(dp->d_name) <= strlen(extension))
                continue;

            if(strcmp(&dp->d_name[strlen(dp->d_name) - strlen(extension)], extension))
                continue;

            files.push_back(dp->d_name);
        }
        closedir(dir);
    }

    return files;
}
