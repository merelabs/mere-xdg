#include "basedirectory.h"
#include "environment.h"

#include "mere/utils/envutils.h"
#include "mere/utils/pathutils.h"

#include <sstream>

Mere::XDG::BaseDirectory::BaseDirectory()
{
}

unsigned int Mere::XDG::BaseDirectory::setupEnv()
{
    int result = 0;

    result += setupDesktopEnv();
    result += setupDataHomeEnv();
    result += setupConfigHomeEnv();
    result += setupIconHomeEnv();
    result += setupDataDirsEnv();
    result += setupConfigDirsEnv();
    result += setupCacheHomeEnv();
    result += setupRuntimeDirEnv();

    return result;
}

unsigned int Mere::XDG::BaseDirectory::setupEnvVar(const char* env, const char* value, unsigned int err)
{
    std::string str(value);
    Mere::Utils::EnvUtils::expandEnvVar(str);

    int result = setenv(env, str.c_str(), 1);
    if (result != 0) return err;

    Mere::Utils::PathUtils::create_if_none(str);

    return 0;
}

unsigned int Mere::XDG::BaseDirectory::setupDesktopEnv()
{
    int result = setenv(Env::Name::SESSION_DESKTOP, Env::Value::SESSION_DESKTOP, 1);
    if (result != 0) return XDG::Env::ErrorMask::SESSION_DESKTOP;

    result = setenv(Env::Name::CURRENT_DESKTOP, Env::Value::CURRENT_DESKTOP, 1);
    if (result != 0) return Env::ErrorMask::CURRENT_DESKTOP;

    return 0;
}

unsigned int Mere::XDG::BaseDirectory::setupDataHomeEnv()
{
    return setupEnvVar(Env::Name::DATA_HOME, Env::Value::DATA_HOME, Env::ErrorMask::DATA_HOME);
}

unsigned int Mere::XDG::BaseDirectory::setupConfigHomeEnv()
{
    return setupEnvVar(Env::Name::CONFIG_HOME, Env::Value::CONFIG_HOME, Env::ErrorMask::CONFIG_HOME);
}

unsigned int Mere::XDG::BaseDirectory::setupIconHomeEnv()
{
    return setupEnvVar(Env::Name::ICON_HOME, Env::Value::ICON_HOME, Env::ErrorMask::ICON_HOME);
}

unsigned int Mere::XDG::BaseDirectory::setupDataDirsEnv()
{
    int result = setenv(Env::Name::DATA_DIRS, Env::Value::DATA_DIRS, Env::ErrorMask::DATA_DIRS);
    if (result != 0) return 4;

    const char *dirs = getenv(Env::Name::DATA_DIRS);
    std::string dataDirs(dirs ? dirs : Env::Value::DATA_DIRS);

    //Mere::Utils::PathUtils::create_if_none(dataDirs);

    return 0;
}

unsigned int Mere::XDG::BaseDirectory::setupConfigDirsEnv()
{
    int result = setenv(Env::Name::CONFIG_DIRS, Env::Value::CONFIG_DIRS, Env::ErrorMask::CONFIG_DIRS);
    if (result != 0) return 8;

    return 0;
}

unsigned int Mere::XDG::BaseDirectory::setupCacheHomeEnv()
{
    return BaseDirectory::setupEnvVar(Env::Name::CACHE_HOME, Env::Value::CACHE_HOME, Env::ErrorMask::CACHE_HOME);
}

unsigned int Mere::XDG::BaseDirectory::setupRuntimeDirEnv()
{
    return BaseDirectory::setupEnvVar(Env::Name::RUNTIME_DIR, Env::Value::RUNTIME_DIR, Env::ErrorMask::RUNTIME_DIR);
}

std::string Mere::XDG::BaseDirectory::dataHome()
{
    const char *home = getenv(XDG::Env::Name::DATA_HOME);

    std::string dataHome(home ? home : Env::Value::DATA_HOME);

    Mere::Utils::EnvUtils::expandEnvVar(dataHome);

    Mere::Utils::PathUtils::create_if_none(dataHome);

    if(dataHome.back() != '/') dataHome.append("/");

    return dataHome;
}

std::string Mere::XDG::BaseDirectory::configHome()
{
    const char *home = getenv(XDG::Env::Name::CONFIG_HOME);

    std::string configHome(home ? home : Env::Value::CONFIG_HOME);

    Mere::Utils::EnvUtils::expandEnvVar(configHome);

    Mere::Utils::PathUtils::create_if_none(configHome);

    if(configHome.back() != '/') configHome.append("/");

    return configHome;
}

std::string Mere::XDG::BaseDirectory::cacheHome()
{
    const char *home = getenv(XDG::Env::Name::CACHE_HOME);

    std::string cacheHome( home ? home : Env::Value::CACHE_HOME);

    Mere::Utils::EnvUtils::expandEnvVar(cacheHome);

    Mere::Utils::PathUtils::create_if_none(cacheHome);

    if(cacheHome.back() != '/') cacheHome.append("/");

    return cacheHome;
}

std::string Mere::XDG::BaseDirectory::iconHome()
{
    const char *home = getenv(XDG::Env::Name::ICON_HOME);

    std::string iconHome( home ? home : Env::Value::ICON_HOME);

    Mere::Utils::EnvUtils::expandEnvVar(iconHome);
    Mere::Utils::PathUtils::create_if_none(iconHome);

    if(iconHome.back() != '/') iconHome.append("/");

    return iconHome;
}

std::vector<std::string> Mere::XDG::BaseDirectory::dataDirectories()
{    
    std::vector<std::string> dirs;

    const char *datadirs = getenv(XDG::Env::Name::DATA_DIRS);

    std::string dataDirectories(datadirs ? datadirs : Env::Value::DATA_DIRS);

    std::string dir;
    std::istringstream iss(dataDirectories);
    while (std::getline(iss, dir, ':'))
    {
        Mere::Utils::EnvUtils::expandEnvVar(dir);
        Mere::Utils::PathUtils::create_if_none(dir);
        if(dir.back() != '/') dir.append("/");

        dirs.push_back(dir);
    }

    return dirs;
}

std::vector<std::string> Mere::XDG::BaseDirectory::configDirectories()
{
    std::vector<std::string> dirs;

    const char *configdirs = getenv(Env::Name::CONFIG_DIRS);

    std::string configDirectories(configdirs ? configdirs : Env::Value::CONFIG_DIRS);

    std::string dir;
    std::istringstream iss(configDirectories);
    while (std::getline(iss, dir, ':'))
    {
        Mere::Utils::EnvUtils::expandEnvVar(dir);
        Mere::Utils::PathUtils::create_if_none(dir);
        if(dir.back() != '/') dir.append("/");

        dirs.push_back(dir);
    }

    return dirs;
}
