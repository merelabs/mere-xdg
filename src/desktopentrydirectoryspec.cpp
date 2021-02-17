#include "desktopentrydirectoryspec.h"
#include "basedirectoryspec.h"

#include "mere/utils/envutils.h"
#include "mere/utils/stringutils.h"

//static
std::vector<std::string> Mere::XDG::DesktopEntryDirectorySpec::applicationDirectories()
{
    std::vector<std::string> applicationDirectories;

    std::string userDatHome = Mere::XDG::BaseDirectorySpec::userDataDirectory();

    Mere::Utils::EnvUtils::expandEnvVar(userDatHome);
    if (Mere::Utils::StringUtils::isNotBlank(userDatHome))
        applicationDirectories.push_back(applicationDirectory(userDatHome));

    const std::vector<std::string> dataSearchDirectories = BaseDirectorySpec::dataSearchDirectories();
    for(std::string dataSearchDirectory : dataSearchDirectories)
    {
        Mere::Utils::EnvUtils::expandEnvVar(dataSearchDirectory);
        if (Mere::Utils::StringUtils::isNotBlank(dataSearchDirectory))
            applicationDirectories.push_back(applicationDirectory(dataSearchDirectory));
    }

    return applicationDirectories;
}

//static
std::string Mere::XDG::DesktopEntryDirectorySpec::applicationDirectory(const std::string &path)
{
    std::string applicationDirectory(path);

    if (applicationDirectory[applicationDirectory.length() - 1] != '/')
        applicationDirectory.append("/");

    return applicationDirectory.append(Mere::XDG::APPLICATION_DIRECTORY);
}
