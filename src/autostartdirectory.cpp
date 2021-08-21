#include "autostartdirectory.h"
#include "basedirectory.h"

#include "mere/utils/envutils.h"
#include "mere/utils/stringutils.h"

static const std::string AUTOSTART_DIRECTORY = "autostart/";
std::vector<std::string> Mere::XDG::AutostartDirectory::directories()
{
    std::vector<std::string> autostartDirectories;

    std::string userConfigHome = BaseDirectory::configHome();
    Mere::Utils::EnvUtils::expandEnvVar(userConfigHome);

    if (Mere::Utils::StringUtils::isNotBlank(userConfigHome))
        autostartDirectories.push_back( Mere::XDG::AutostartDirectory::directory(userConfigHome) );

    const std::vector<std::string> directories = BaseDirectory::configDirectories();
    for (std::string directory : directories)
    {
        Mere::Utils::EnvUtils::expandEnvVar(directory);

        if (Mere::Utils::StringUtils::isNotBlank(directory))
            autostartDirectories.push_back( Mere::XDG::AutostartDirectory::directory(directory) );
    }

    return autostartDirectories;
}

std::string Mere::XDG::AutostartDirectory::directory(const std::string &path)
{
    std::string autostartDirectory(path);

    if (autostartDirectory.back() != '/')
        autostartDirectory.append("/");

    return autostartDirectory.append(AUTOSTART_DIRECTORY);
}
