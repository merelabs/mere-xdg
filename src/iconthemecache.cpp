#include "iconthemecache.h"


std::map<std::string, Mere::XDG::IconTheme> Mere::XDG::IconThemeCache::m_cache = {};

//static
bool Mere::XDG::IconThemeCache::findTheme(const std::string &key, IconTheme *theme)
{
    auto find = m_cache.find(key);
    if (find == m_cache.end())
        return false;

    *theme = find->second;

    return true;
}

//static
bool Mere::XDG::IconThemeCache::insertTheme(const std::string &key, IconTheme &theme)
{
    m_cache.insert({key, theme});
    return true;
}

//static
bool Mere::XDG::IconThemeCache::removeTheme(const std::string &key)
{
    m_cache.erase(key);

   return true;
}
