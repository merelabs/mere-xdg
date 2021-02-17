#include "iconthemedirectoryspec.h"
#include "basedirectoryspec.h"

#include "mere/utils/envutils.h"
#include "mere/utils/stringutils.h"

#include <iostream>
#include <fstream>
#include <QDir>

//static
std::vector<std::string> Mere::XDG::IconThemeDirectorySpec::baseDirectories()
{
    std::vector<std::string> iconDirectories;

    std::string userIconHome = IconThemeDirectorySpec::userIconDirectory();
    Mere::Utils::EnvUtils::expandEnvVar(userIconHome);

    if (Mere::Utils::StringUtils::isNotBlank(userIconHome))
        iconDirectories.push_back(userIconHome);

    // Not in specification
    std::string userDataDirectory = BaseDirectorySpec::userDataDirectory();
    Mere::Utils::EnvUtils::expandEnvVar(userDataDirectory);

    if (Mere::Utils::StringUtils::isNotBlank(userDataDirectory))
        iconDirectories.push_back(iconDirectory(userDataDirectory));

    const std::vector<std::string> dataSearchDirectories = BaseDirectorySpec::dataSearchDirectories();
    for(std::string dataSearchDirectory : dataSearchDirectories)
    {
        Mere::Utils::EnvUtils::expandEnvVar(dataSearchDirectory);
        if (Mere::Utils::StringUtils::isNotBlank(dataSearchDirectory))
            iconDirectories.push_back(iconDirectory(dataSearchDirectory));
    }

    // Not in specification
    iconDirectories.push_back("/usr/local/share/pixmaps");
    iconDirectories.push_back("/usr/share/pixmaps");

    return iconDirectories;
}

//static
std::vector<std::string> Mere::XDG::IconThemeDirectorySpec::themeDirectories(const std::string &theme)
{
    std::vector<std::string> themeDirectories;

    std::vector<std::string> baseDirectories = IconThemeDirectorySpec::baseDirectories();
    for ( const std::string &baseDirectory : baseDirectories  )
    {
        std::string themeDirectory = baseDirectory;
        themeDirectory.append("/").append(theme);

        std::string indexThemeFilePath = themeDirectory;
        indexThemeFilePath.append("/").append("index.theme");

        if(std::ifstream(indexThemeFilePath).good())
            themeDirectories.push_back(themeDirectory);
    }

    return themeDirectories;
}

//static
std::string Mere::XDG::IconThemeDirectorySpec::iconDirectory(const std::string &path)
{
    std::string iconPath(path);

    if (path[path.length() - 1] != '/')
        iconPath = iconPath.append("/");

    return iconPath.append(XDG::ICON_DIRECTORY);
}

//static
std::string Mere::XDG::IconThemeDirectorySpec::userIconDirectory()
{
    std::string iconHome = getenv(XDG::ICON_HOME);

    if(Mere::Utils::StringUtils::isBlank(iconHome))
        iconHome = XDG::BaseDirectory::ICON_HOME;

    Mere::Utils::EnvUtils::expandEnvVar(iconHome);

    if(!std::fstream(iconHome).good())
        QDir().mkpath(iconHome.c_str());

    return iconHome;
}
