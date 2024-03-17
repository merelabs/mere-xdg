#ifndef ICONTHEMECACHE_H
#define ICONTHEMECACHE_H

#include "global.h"
#include "icontheme.h"

#include <map>


namespace Mere::XDG
{

class MERE_XDG_LIB_SPEC IconThemeCache
{
    IconThemeCache() = default;
public:
    static bool findTheme(const std::string &key, IconTheme *theme);
    static bool insertTheme(const std::string &key, IconTheme &theme);
    static bool removeTheme(const std::string &key);

private:
    static std::map<std::string, IconTheme> m_cache;
};

}


#endif // ICONTHEMECACHE_H
