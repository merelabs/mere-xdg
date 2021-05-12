#include "iconthemedirectorytraverser.h"
#include "iconthemedirectory.h"
#include "iconthemeparser.h"

#include "dirent.h"
#include <fstream>

Mere::XDG::IconThemeDirectoryTraverser::IconThemeDirectoryTraverser(QObject *parent) : QObject(parent)
{
}

std::vector<Mere::XDG::IconTheme> Mere::XDG::IconThemeDirectoryTraverser::traverse() const
{
    std::vector<Mere::XDG::IconTheme> themes;

    for(const std::string &directory : IconThemeDirectory::directories())
    {
        std::vector<Mere::XDG::IconTheme> _themes = this->traverse(directory);
        if (_themes.empty()) continue;
        themes.insert(themes.end(), std::make_move_iterator(_themes.begin()), std::make_move_iterator(_themes.end()));
    }

    return themes;
}

std::vector<Mere::XDG::IconTheme> Mere::XDG::IconThemeDirectoryTraverser::traverse(const std::string &path) const
{
    std::vector<Mere::XDG::IconTheme> themes;

    std::string base(path);

    std::vector<std::string> files = this->files(path);
    for(const std::string &file : files)
    {
        std::string p(base);
        IconThemeParser parser(p.append(file));

        IconTheme theme = parser.parse();
        if(!theme.valid()) continue;

        themes.push_back(std::move(theme));
    }

    emit traversed(path);

    return themes;
}


std::map<std::string, std::vector<std::string>> Mere::XDG::IconThemeDirectoryTraverser::files() const
{
    std::map<std::string, std::vector<std::string>> files;

    std::vector<std::string> directoris = Mere::XDG::IconThemeDirectory::directories();
    for(const std::string &directory : directoris)
    {
        std::vector<std::string> _files = this->files(directory);
        if (_files.empty()) continue;

        files.insert({directory, std::move(_files)});
    }

    return files;
}

std::vector<std::string> Mere::XDG::IconThemeDirectoryTraverser::files(const std::string &path) const
{
    std::vector<std::string> files;

    if (path.empty()) return files;

    std::string base(path);

    if (DIR *dir = opendir(path.c_str()))
    {
        const char *themefile = "/index.theme";

        struct dirent *dp;
        while ((dp = readdir(dir)))
        {
            if (dp->d_type != DT_DIR) continue;
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0 )
                continue;

            std::string p(base);
            p.append(dp->d_name).append(themefile);

            if(!std::ifstream(p).good()) continue;

            files.push_back(std::string(dp->d_name).append(themefile));
        }
        closedir(dir);
    }

    return files;
}
