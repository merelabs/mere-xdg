#include "iconlookuphelper.h"
#include "iconthemedirectory.h"
#include "icondirectorytraverser.h"
#include "iconthemedirectorytraverser.h"
#include "config.h"

#include "mere/utils/fileutils.h"

#include <iostream>
#include <chrono>

#include <QDir>

//static
std::string Mere::XDG::IconLookupHelper::path(const std::string &icon)
{    
    auto pos = icon.find("/");
    if(pos == 0) return icon;

    pos = icon.find("./");
    if(pos == 0) return icon;

    auto start = std::chrono::high_resolution_clock::now();

    std::string path = LookupIcon(icon);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Lookup time: " << duration.count() << std::endl;

    return path;
}

//static
std::string Mere::XDG::IconLookupHelper::LookupIcon(const std::string &icon)
{
    IconThemeDirectoryTraverser traverser;
    std::vector<Mere::XDG::IconTheme> themes = traverser.traverse();

    Config *config = Config::instance();

    config->theme("Adwaita");
    config->size(48);
    config->context("");

//    qDebug() << "CONFIG::================================";
//    qDebug() << "Theme  : " << config->theme().c_str();
//    qDebug() << "Size   : " << config->size();
//    qDebug() << "Context: " << config->context().c_str();
//    qDebug() << "CONFIG::================================";

    std::string path;

    // user theme
    for(const auto &theme : themes)
    {
        if(theme.hidden()) continue;
        if (!config->theme().empty() && theme.name().compare(config->theme())) continue;

        path = LookupIcon(icon, theme);
        break;
    }

    // fallback theme
    if (path.empty())
    {
        for(const auto &theme : themes)
        {
            if(!theme.hidden()) continue;
            if (theme.name().compare("Hicolor")) continue;

            path = LookupIcon(icon, theme);
            break;
        }
    }

    // check in base directories
    if (path.empty())
        path = LookupFallbackIcon(icon);

    return path;
}


//static
std::string Mere::XDG::IconLookupHelper::LookupIcon(const std::string &icon, const IconTheme &theme)
{
    if (icon.empty() || !theme.valid()) return "";

    std::vector<IconThemeSubDirectory> directories = theme.subdirectories();
    if (!directories.size()) return "";

    Config *config = Config::instance();

    // filter by context
    if (!config->context().empty())
    {
        auto it = std::remove_if(directories.begin(), directories.end(), [config](const IconThemeSubDirectory &directory)
        {
            return directory.context().compare(config->context());
        });

        directories.erase(it, directories.end());
    }


    std::string iconName(name(icon));

    std::string iconPath;


    int minsize = INT_MAX;

    IconDirectoryTraverser traverser;
    for(const auto &directory : directories)
    {
        std::string p(directory.home());
        p.append(directory.id()).append("/");

        std::vector<std::string> icons = traverser.traverse(p, iconName);
        if (!icons.size()) continue;

        if (config->size() == 0 || DirectoryMatchesSize(directory, config->size(), config->scale()))
        {
            iconPath = icons.at(0);
            break;
        }
        else
        {
            int distance = DirectorySizeDistance(directory, config->size(), config->scale());
            if( distance < minsize)
            {
                iconPath = icons.at(0);
                minsize = distance;
            }
        }
    }

    return iconPath;
}

//static
std::vector<std::string> Mere::XDG::IconLookupHelper::filters(const std::string &icon)
{
    const std::vector<std::string> extensions = {".png", ".svg", ".xpm"};

    std::string file(icon);
    if (file.length() > 4)
    {
        std::string ext = icon.substr(icon.length() - 4);

        // why? - last dot does not mean to start of the ext
        for(const std::string &extension : extensions)
        {
            if (extension.compare(ext)) continue;
            file.erase(icon.length() - 4);
            break;
        }
    }

    std::vector<std::string> filters;
    for (const std::string &extension : extensions)
        filters.push_back(std::string(file).append(extension));

    return filters;
}

//static
bool Mere::XDG::IconLookupHelper::DirectoryMatchesSize(const IconThemeSubDirectory &def, unsigned int size, unsigned int  scale)
{
    if (def.scale() != scale)
         return false;

    if (def.type().compare("Fixed") == 0)
        return def.size() == size;

    if (def.type().compare("Scaled") == 0)
        return def.minsize() <= size && size <= def.maxsize();

    if (def.type().compare("Threshold") == 0)
        return (def.size() - def.threshold()) <= size && size <= (def.size() + def.threshold());

    return false;
}

//static
int Mere::XDG::IconLookupHelper::DirectorySizeDistance(const IconThemeSubDirectory &def, unsigned int size, unsigned int scale)
{
    if (def.type().compare("Fixed") == 0)
        return def.size() * def.scale() - size * scale;

    if (def.type().compare("Scaled") == 0)
    {
        if (size * scale < def.minsize() * def.scale())
            return def.minsize() * def.scale() - size * scale;

        if (size * scale > def.minsize() * def.scale())
            return size * scale - def.minsize() * def.scale();

        return 0;
    }

    if (def.type().compare("Threshold") == 0)
    {
        if ( size * scale < (def.size() - def.threshold()) * def.scale())
            return def.minsize() * def.scale() - size * scale;

        if ( size * scale > (def.size() + def.threshold()) * def.scale())
            return size * scale - def.maxsize() * def.scale();

        return 0;
    }

    return 0;
}

std::string Mere::XDG::IconLookupHelper::LookupFallbackIcon(const std::string &icon)
{
    std::vector<std::string> filters = IconLookupHelper::filters(icon);

    const std::vector<std::string> &directories = IconThemeDirectory::base();
    for (const std::string &directory : directories)
    {
        for (const std::string &filter : filters)
        {
            std::string path(directory);
            path.append(filter);
            if (Mere::Utils::FileUtils::isExist(path))
                return path;
        }
    }

    return "";
}

//static
std::string Mere::XDG::IconLookupHelper::name(const std::string &icon)
{
    const std::vector<std::string> extensions = {".png", ".svg", ".xpm"};

    std::string name(icon);
    if (name.length() > 4)
    {
        std::string ext = icon.substr(icon.length() - 4);

        // why? - last dot does not mean to start of the ext
        for(const std::string &extension : extensions)
        {
            if (extension.compare(ext)) continue;
            name.erase(icon.length() - 4);
            break;
        }
    }

    return name;
}
