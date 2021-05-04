#include "icondirectorytraverser.h"

#include <sys/types.h>
#include <dirent.h>

Mere::XDG::IconDirectoryTraverser::IconDirectoryTraverser(QObject *parent) : QObject(parent)
{

}

std::vector<std::string> Mere::XDG::IconDirectoryTraverser::traverse(const std::string &path, const std::string &name) const
{
    std::vector<std::string> icons;

    std::string base(path);

    std::vector<std::string> files = this->files(path, name);
    for(const std::string &file : files)
    {
        std::string p(base);
        p.append(file);
        icons.push_back(std::move(p));
    }

    return icons;
}
std::vector<std::string> Mere::XDG::IconDirectoryTraverser::files(const std::string &path, const std::string &name) const
{
    std::vector<std::string> files;

    if (path.empty()) return files;

    if (DIR *dir = opendir(path.c_str()))
    {
        struct dirent *dp;
        while ((dp = readdir(dir)))
        {
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0 )
                continue;

            if (strlen(dp->d_name) != (name.length() + 4))
                continue;

            if(strncmp(dp->d_name, name.c_str(), name.length()))
                continue;

            files.push_back(dp->d_name);
        }
        closedir(dir);
    }

    return files;
}
