#include "basedirectoryspec.h"

#include "mere/utils/envutils.h"
#include "mere/utils/stringutils.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include <QDir>
#include <QDebug>

Mere::XDG::BaseDirectorySpec::BaseDirectorySpec()
{

}

unsigned int Mere::XDG::BaseDirectorySpec::setupEnv()
{
    int result = 0;

    result += setupDesktopEnv();
    result += setupDataHomeEnv();
    result += setupConfigHomeEnv();
    result += setupDataDirsEnv();
    result += setupConfigDirsEnv();
    result += setupCacheHomeEnv();
    result += setupRuntimeDirEnv();

    return result;
}

unsigned int Mere::XDG::BaseDirectorySpec::setupEnvVar(const char* env, const char* value, unsigned int err)
{
    std::string str(value);
    Mere::Utils::EnvUtils::expandEnvVar(str);

    int result = setenv(env, str.c_str(), 1);
    if (result != 0) return err;

    if (!std::ifstream(str).good())
        QDir().mkpath(str.c_str());

    return 0;
}

unsigned int Mere::XDG::BaseDirectorySpec::setupDesktopEnv()
{
    int result = setenv(XDG::SESSION_DESKTOP, XDG::BaseDirectory::SESSION_DESKTOP, 1);
    if (result != 0) return XDG::ErrorMask::SESSION_DESKTOP;

    result = setenv(XDG::CURRENT_DESKTOP, XDG::BaseDirectory::CURRENT_DESKTOP, 1);
    if (result != 0) return XDG::ErrorMask::CURRENT_DESKTOP;

    return 0;
}

unsigned int Mere::XDG::BaseDirectorySpec::setupDataHomeEnv()
{
    return setupEnvVar(XDG::DATA_HOME, XDG::BaseDirectory::DATA_HOME, XDG::ErrorMask::DATA_HOME);
}

unsigned int Mere::XDG::BaseDirectorySpec::setupConfigHomeEnv()
{
    return setupEnvVar(XDG::CONFIG_HOME, XDG::BaseDirectory::CONFIG_HOME, XDG::ErrorMask::CONFIG_HOME);
}

unsigned int Mere::XDG::BaseDirectorySpec::setupDataDirsEnv()
{
    int result = setenv(XDG::DATA_DIRS, XDG::BaseDirectory::DATA_DIRS, XDG::ErrorMask::DATA_DIRS);
    if (result != 0) return 4;

    std::string dataDirs(getenv(XDG::DATA_DIRS));

    if (!std::ifstream(dataDirs).good())
        QDir().mkpath(dataDirs.c_str());

    return 0;
}

unsigned int Mere::XDG::BaseDirectorySpec::setupConfigDirsEnv()
{
    int result = setenv(XDG::CONFIG_DIRS, XDG::BaseDirectory::CONFIG_DIRS, XDG::ErrorMask::CONFIG_DIRS);
    if (result != 0) return 8;

    QString configDirs(getenv(XDG::CONFIG_DIRS));

    return 0;
}

unsigned int Mere::XDG::BaseDirectorySpec::setupCacheHomeEnv()
{
    return BaseDirectorySpec::setupEnvVar(XDG::CACHE_HOME, XDG::BaseDirectory::CACHE_HOME, XDG::ErrorMask::CACHE_HOME);
}

unsigned int Mere::XDG::BaseDirectorySpec::setupRuntimeDirEnv()
{
    return BaseDirectorySpec::setupEnvVar(XDG::RUNTIME_DIR, XDG::BaseDirectory::RUNTIME_DIR, XDG::ErrorMask::RUNTIME_DIR);
}

std::string Mere::XDG::BaseDirectorySpec::userDataDirectory()
{
    const char *home = getenv(XDG::DATA_HOME);

    std::string dataHome(home ? home : XDG::BaseDirectory::DATA_HOME);

    Mere::Utils::EnvUtils::expandEnvVar(dataHome);

    if (!std::ifstream(dataHome).good())
        QDir().mkpath(dataHome.c_str());

    return dataHome;
}

std::string Mere::XDG::BaseDirectorySpec::userConfigDirectory()
{
    const char *home = getenv(XDG::CONFIG_HOME);

    std::string configHome(home ? home : XDG::BaseDirectory::CONFIG_HOME);

    Mere::Utils::EnvUtils::expandEnvVar(configHome);

    if (!std::ifstream(configHome).good())
        QDir().mkpath(configHome.c_str());

    return configHome;
}

std::string Mere::XDG::BaseDirectorySpec::userCacheDirectory()
{
    const char *home = getenv(XDG::CACHE_HOME);

    std::string cacheHome( home ? home : XDG::BaseDirectory::CACHE_HOME);

    Mere::Utils::EnvUtils::expandEnvVar(cacheHome);

    if (!std::ifstream(cacheHome).good())
        QDir().mkpath(cacheHome.c_str());

    return cacheHome;
}

std::vector<std::string> Mere::XDG::BaseDirectorySpec::dataSearchDirectories()
{    
    std::vector<std::string> dirs;

    const char *datadirs = getenv(XDG::DATA_DIRS);

    std::string dataDirectories(datadirs ? datadirs : XDG::BaseDirectory::DATA_DIRS);

    std::string dir;
    std::istringstream iss(dataDirectories);
    while (std::getline(iss, dir, ':'))
    {
        Mere::Utils::EnvUtils::expandEnvVar(dir);
        if (!std::ifstream(dir).good())
            QDir().mkpath(dir.c_str());

        dirs.push_back(dir);
    }

    return dirs;
}

std::vector<std::string> Mere::XDG::BaseDirectorySpec::configSearchDirectories()
{
    std::vector<std::string> dirs;

    const char *configdirs = getenv(XDG::CONFIG_DIRS);

    std::string configDirectories(configdirs ? configdirs : XDG::BaseDirectory::CONFIG_DIRS);

    std::string dir;
    std::istringstream iss(configDirectories);
    while (std::getline(iss, dir, ':'))
    {
        Mere::Utils::EnvUtils::expandEnvVar(dir);
        if (!std::ifstream(dir).good())
            QDir().mkpath(dir.c_str());

        dirs.push_back(dir);
    }

    return dirs;
}
