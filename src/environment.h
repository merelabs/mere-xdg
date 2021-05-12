#ifndef MERE_XDG_ENV_H
#define MERE_XDG_ENV_H

namespace Mere
{
namespace XDG
{

namespace Env
{
    namespace Name
    {
        extern const char* SESSION_DESKTOP;
        extern const char* CURRENT_DESKTOP;

        extern const char* DATA_HOME;
        extern const char* CONFIG_HOME;
        extern const char* CACHE_HOME;
        extern const char* ICON_HOME;

        extern const char* DATA_DIRS;
        extern const char* CONFIG_DIRS;

        extern const char* RUNTIME_DIR;
    }

    namespace Value
    {
        extern const char* SESSION_DESKTOP;
        extern const char* CURRENT_DESKTOP;

        extern const char* DATA_HOME;
        extern const char* CONFIG_HOME;
        extern const char* CACHE_HOME;
        extern const char* ICON_HOME;

        extern const char* DATA_DIRS;

        // we made a bit change here; added /usr/local/etc/xdg
        extern const char* CONFIG_DIRS;

        // where did we find this one, in which spec?
        extern const char* RUNTIME_DIR;
    }

    namespace ErrorMask
    {
        const unsigned int SESSION_DESKTOP = 1 << 1;
        const unsigned int CURRENT_DESKTOP = 1 << 2;
        const unsigned int DATA_HOME       = 1 << 3;
        const unsigned int CONFIG_HOME     = 1 << 4;
        const unsigned int CACHE_HOME      = 1 << 5;
        const unsigned int ICON_HOME       = 1 << 6;
        const unsigned int DATA_DIRS       = 1 << 7;
        const unsigned int CONFIG_DIRS     = 1 << 8;
        const unsigned int RUNTIME_DIR     = 1 << 9;
    }
}

}
}

#endif // MERE_XDG_ENV_H
