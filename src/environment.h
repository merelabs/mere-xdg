#ifndef MERE_XDG_ENV_H
#define MERE_XDG_ENV_H

#include <iostream>

namespace Mere::XDG::Env
{
    namespace Name
    {
        static constexpr char SESSION_DESKTOP[] = "XDG_SESSION_DESKTOP";
        static constexpr char CURRENT_DESKTOP[] = "XDG_CURRENT_DESKTOP";

        static constexpr char DATA_HOME[]       = "XDG_DATA_HOME";
        static constexpr char CONFIG_HOME[]     = "XDG_CONFIG_HOME";
        static constexpr char CACHE_HOME[]      = "XDG_CACHE_HOME";
        static constexpr char ICON_HOME[]       = "XDG_ICON_HOME";

        static constexpr char DATA_DIRS[]       = "XDG_DATA_DIRS";
        static constexpr char CONFIG_DIRS[]     = "XDG_CONFIG_DIRS";

        static constexpr char RUNTIME_DIR[]     = "XDG_RUNTIME_DIR";
    }

    namespace Value
    {
        static constexpr char SESSION_DESKTOP[] = "MERE";
        static constexpr char CURRENT_DESKTOP[] = "MERE";

        static constexpr char DATA_HOME[]       = "$HOME/.local/share/";
        static constexpr char CONFIG_HOME[]     = "$HOME/.config/";
        static constexpr char CACHE_HOME[]      = "$HOME/.cache/";
        static constexpr char ICON_HOME[]       = "$HOME/.icons/";

        static constexpr char DATA_DIRS[]       = "/usr/local/share/:/usr/share/";

        // we made a bit change here; added /usr/local/etc/xdg
        static constexpr char CONFIG_DIRS[]     = "/usr/local/etc/xdg/:/etc/xdg/";

        // where did we find this one, in which spec?
        static constexpr char RUNTIME_DIR[]     = "/tmp/mere-$USER/";
    }

    namespace ErrorMask
    {
        static constexpr unsigned int SESSION_DESKTOP = 1 << 1;
        static constexpr unsigned int CURRENT_DESKTOP = 1 << 2;
        static constexpr unsigned int DATA_HOME       = 1 << 3;
        static constexpr unsigned int CONFIG_HOME     = 1 << 4;
        static constexpr unsigned int CACHE_HOME      = 1 << 5;
        static constexpr unsigned int ICON_HOME       = 1 << 6;
        static constexpr unsigned int DATA_DIRS       = 1 << 7;
        static constexpr unsigned int CONFIG_DIRS     = 1 << 8;
        static constexpr unsigned int RUNTIME_DIR     = 1 << 9;
    }
}


#endif // MERE_XDG_ENV_H
