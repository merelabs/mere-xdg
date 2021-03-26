#include "desktopentrydirectory.h"
#include "basedirectory.h"
#include "desktopentryhelper.h"

#include "mere/utils/envutils.h"
#include "mere/utils/binutils.h"
#include "mere/utils/stringutils.h"

#include <QDir>

//static
std::vector<std::string> Mere::XDG::DesktopEntryDirectory::directories()
{
    std::vector<std::string> applicationDirectories;

    std::string userDatHome = Mere::XDG::BaseDirectory::dataHome();

    Mere::Utils::EnvUtils::expandEnvVar(userDatHome);
    if (Mere::Utils::StringUtils::isNotBlank(userDatHome))
        applicationDirectories.push_back(directory(userDatHome));

    const std::vector<std::string> dataSearchDirectories = BaseDirectory::dataDirectories();
    for(std::string dataSearchDirectory : dataSearchDirectories)
    {
        Mere::Utils::EnvUtils::expandEnvVar(dataSearchDirectory);
        if (Mere::Utils::StringUtils::isNotBlank(dataSearchDirectory))
            applicationDirectories.push_back(directory(dataSearchDirectory));
    }

    return applicationDirectories;
}

//static
std::string Mere::XDG::DesktopEntryDirectory::directory(const std::string &path)
{
    std::string applicationDirectory(path);

    if (applicationDirectory.back() != '/')
        applicationDirectory.append("/");

    return applicationDirectory.append(Mere::XDG::APPLICATION_DIRECTORY);
}
