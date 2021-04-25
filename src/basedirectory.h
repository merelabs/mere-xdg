#ifndef MERE_XDG_DIRECTORYSPEC_H
#define MERE_XDG_DIRECTORYSPEC_H

#include "global.h"

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC BaseDirectory
{

private:
    BaseDirectory();

public:
    /**
     * @brief setupEnv
     *
     * Setup environments variables specified in XDG base directory specification.
     * - XDG_DATA_HOME
     * - XDG_CONFIG_HOME
     * - XDG_CACHE_HOME
     * - XDG_DATA_DIRS
     * - XDG_CONFIG_DIRS
     *
     * - XDG_ICON_HOME
     * - XDG_SESSION_DESKTOP
     * - XDG_CURRENT_DESKTOP
     * - XDG_RUNTIME_DIR
     * @return
     */
    static unsigned int setupEnv();

    /**
     * @brief userDataDirectory
     *
     * Single base directory relative to which user-specific data files should be written.
     * This directory is defined by the environment variable $XDG_DATA_HOME.
     *
     * If $XDG_DATA_HOME is either not set or empty, a default equal to $HOME/.local/share should be used.
     *
     * @return
     */
    static std::string  dataHome();

    /**
     * @brief userConfigDirectory
     *
     * Single base directory relative to which user-specific configuration files should be written.
     * This directory is defined by the environment variable $XDG_CONFIG_HOME.
     *
     * If $XDG_CONFIG_HOME is either not set or empty, a default equal to $HOME/.config should be used.
     *
     * @return
     */
    static std::string configHome();

    /**
     * @brief userCacheDirectory
     *
     * Base directory relative to which user-specific non-essential (cached) data should be written.
     * This directory is defined by the environment variable $XDG_CACHE_HOME.
     *
     * If $XDG_CACHE_HOME is either not set or empty, a default equal to $HOME/.cache should be used.
     *
     * @return
     */
    static std::string cacheHome();


    // we did we get it?
    static std::string iconHome();

    /**
     * @brief dataSearchDirectories
     *
     * Directories relative to which data files should be searched.
     * This set of directories is defined by the environment variable $XDG_DATA_DIRS.
     *
     * $XDG_DATA_DIRS defines the preference-ordered set of base directories to search for data files in addition to the $XDG_DATA_HOME base directory.
     * The directories in $XDG_DATA_DIRS should be seperated with a colon ':'.
     *
     * If $XDG_DATA_DIRS is either not set or empty, a value equal to /usr/local/share/:/usr/share/ should be used.
     *
     * @return
     */
    static std::vector<std::string> dataDirectories();

    /**
     * @brief configSearchDirectories
     *
     * Directories relative to which configuration files should be searched.
     * This set of directories is defined by the environment variable $XDG_CONFIG_DIRS.
     *
     * $XDG_CONFIG_DIRS defines the preference-ordered set of base directories to search for configuration files in addition to the $XDG_CONFIG_HOME base directory.
     * The directories in $XDG_CONFIG_DIRS should be seperated with a colon ':'.
     *
     * If $XDG_CONFIG_DIRS is either not set or empty, a value equal to /etc/xdg should be used.
     * @return
     */
    static std::vector<std::string> configDirectories();

private:
    static unsigned int setupDesktopEnv();

    /**
     * @brief setupDataHomeEnv
     * User-specific data files store localtion
     * @return
     */
    static unsigned int setupDataHomeEnv();

    /**
     * @brief setupConfigHomeEnv
     * User-specific configuration files store localtion
     * @return
     */
    static unsigned int setupConfigHomeEnv();
    static unsigned int setupDataDirsEnv();
    static unsigned int setupConfigDirsEnv();
    static unsigned int setupCacheHomeEnv();
    static unsigned int setupIconHomeEnv();
    static unsigned int setupRuntimeDirEnv();

    static unsigned int setupEnvVar(const char *env, const char *value, unsigned int err);
};

}
}

#endif // MERE_XDG_DIRECTORYSPEC_H
