#include "xsessiondirectory.h"
#include "basedirectory.h"

#include "mere/utils/envutils.h"
#include "mere/utils/stringutils.h"

static const std::string XSESSION_DIRECTORY = "xsessions/";

//static
std::vector<std::string> Mere::XDG::XSessionDirectory::directories()
{
    std::vector<std::string> sessionDirectories;

    std::string userDatHome = Mere::XDG::BaseDirectory::dataHome();

    Mere::Utils::EnvUtils::expandEnvVar(userDatHome);
    if (Mere::Utils::StringUtils::isNotBlank(userDatHome))
        sessionDirectories.push_back(directory(userDatHome));

    const std::vector<std::string> dataSearchDirectories = BaseDirectory::dataDirectories();
    for(std::string dataSearchDirectory : dataSearchDirectories)
    {
        Mere::Utils::EnvUtils::expandEnvVar(dataSearchDirectory);
        if (Mere::Utils::StringUtils::isNotBlank(dataSearchDirectory))
            sessionDirectories.push_back(directory(dataSearchDirectory));
    }

    return sessionDirectories;
}

//static
std::string Mere::XDG::XSessionDirectory::directory(const std::string &path)
{
    std::string applicationDirectory(path);

    if (applicationDirectory.back() != '/')
        applicationDirectory.append("/");

    return applicationDirectory.append(XSESSION_DIRECTORY);
}
