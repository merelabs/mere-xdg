#ifndef MERE_XDG_DIRECTORYSPEC_H
#define MERE_XDG_DIRECTORYSPEC_H

#include "global.h"

class QString;
class QStringList;

namespace Mere
{
namespace XDG
{
    static const char* SESSION_DESKTOP = "XDG_SESSION_DESKTOP";
    static const char* CURRENT_DESKTOP = "XDG_CURRENT_DESKTOP";

    static const char* DATA_HOME   = "XDG_DATA_HOME";
    static const char* CONFIG_HOME = "XDG_CONFIG_HOME";
    static const char* CACHE_HOME  = "XDG_CACHE_HOME";
    static const char* ICON_HOME   = "XDG_ICON_HOME";

    static const char* DATA_DIRS   = "XDG_DATA_DIRS";
    static const char* CONFIG_DIRS = "XDG_CONFIG_DIRS";

    static const char* RUNTIME_DIR = "XDG_RUNTIME_DIR";

    namespace BaseDirectory
    {
        static const char* SESSION_DESKTOP = "mere";
        static const char* CURRENT_DESKTOP = "mere";

        static const char* DATA_HOME   = "$HOME/.local/share/";
        static const char* CONFIG_HOME = "$HOME/.config/";
        static const char* CACHE_HOME  = "$HOME/.cache/";
        static const char* ICON_HOME   = "$HOME/.icons/";

        static const char* DATA_DIRS   = "/usr/local/share/:/usr/share/";

        // we made a bit change here; added /usr/local/etc/xdg
        static const char* CONFIG_DIRS = "/usr/local/etc/xdg/:/etc/xdg/";

        // where did we find this one, in which spec?
        static const char* RUNTIME_DIR = "/tmp/mere-$USER/";
    }

    namespace ErrorMask
    {
        static const unsigned int SESSION_DESKTOP = 1 << 1;
        static const unsigned int CURRENT_DESKTOP = 1 << 2;
        static const unsigned int DATA_HOME       = 1 << 3;
        static const unsigned int CONFIG_HOME     = 1 << 4;
        static const unsigned int CACHE_HOME      = 1 << 5;
        static const unsigned int ICON_HOME       = 1 << 6;
        static const unsigned int DATA_DIRS       = 1 << 7;
        static const unsigned int CONFIG_DIRS     = 1 << 8;
        static const unsigned int RUNTIME_DIR     = 1 << 9;
    }

class MERE_XDG_LIB_SPEC BaseDirectorySpec
{

private:
    BaseDirectorySpec();

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
