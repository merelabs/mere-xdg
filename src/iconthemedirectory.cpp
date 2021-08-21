#include "iconthemedirectory.h"
#include "basedirectory.h"
#include "environment.h"

#include "mere/utils/envutils.h"
#include "mere/utils/pathutils.h"
#include "mere/utils/stringutils.h"

#include <iostream>
#include <fstream>

const std::string ICON_DIRECTORY = "icons/";

//static
std::vector<std::string> Mere::XDG::IconThemeDirectory::directories()
{
    return IconThemeDirectory::base();
}

//static
std::vector<std::string> Mere::XDG::IconThemeDirectory::directories(const std::string &theme)
{
    std::vector<std::string> directories;

    std::vector<std::string> dirs = IconThemeDirectory::base();
    for (const std::string &dir : dirs)
    {
        // check for index.theme
        std::string themeDir(dir);
        themeDir.append("/").append(theme);

        std::string themeIndex(themeDir);
        themeIndex.append("/").append("index.theme");

        if(std::ifstream(themeIndex).good())
            directories.push_back(themeDir);
    }

    return directories;
}

//static
std::string Mere::XDG::IconThemeDirectory::home()
{
    const char *home = getenv(Env::Name::ICON_HOME);

    std::string iconHome(home ? home : Env::Value::ICON_HOME);
    Mere::Utils::EnvUtils::expandEnvVar(iconHome);
    Mere::Utils::PathUtils::create_if_none(iconHome);

    return iconHome;
}

//static
std::vector<std::string> Mere::XDG::IconThemeDirectory::base()
{
    std::vector<std::string> directories;

    std::string home = IconThemeDirectory::home();
    Mere::Utils::EnvUtils::expandEnvVar(home);

    if (Mere::Utils::StringUtils::isNotBlank(home))
        directories.push_back(home);

    // Not in specification
    std::string dataHome= BaseDirectory::dataHome();
    Mere::Utils::EnvUtils::expandEnvVar(dataHome);

    if (Mere::Utils::StringUtils::isNotBlank(dataHome))
        directories.push_back(iconDirectory(dataHome));

    const std::vector<std::string> dataSearchDirectories = BaseDirectory::dataDirectories();
    for(std::string dataSearchDirectory : dataSearchDirectories)
        directories.push_back(iconDirectory(dataSearchDirectory));

    for(const std::string &pixmap : pixmaps())
        directories.push_back(pixmap);

    return directories;
}

//static
std::vector<std::string> Mere::XDG::IconThemeDirectory::pixmaps()
{
    return {"/usr/local/share/pixmaps/", "/usr/share/pixmaps/"};
}

//static
std::string Mere::XDG::IconThemeDirectory::iconDirectory(const std::string &path)
{
    std::string iconPath(path);

    if (path.back() != '/')
        iconPath = iconPath.append("/");

    return iconPath.append(ICON_DIRECTORY);
}
