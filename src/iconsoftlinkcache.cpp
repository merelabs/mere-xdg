#include "iconsoftlinkcache.h"
#include "iconmemorycache.h"

#include "mere/utils/pathutils.h"
#include "mere/utils/fileutils.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>

Mere::XDG::IconSoftLinkCache::~IconSoftLinkCache()
{
}

Mere::XDG::IconSoftLinkCache::IconSoftLinkCache()
    : IconSoftLinkCache("/tmp/mere/xdg/icon/")
{
}

Mere::XDG::IconSoftLinkCache::IconSoftLinkCache(const std::string &path)
    : m_cache(nullptr)
{
    setPath(path);
}

void Mere::XDG::IconSoftLinkCache::setPath(const std::string &path)
{
    if (path.empty()) return;

    m_path = path;

    if(m_path.back() != '/')
        m_path.append("/");

    Mere::Utils::PathUtils::create_if_none(m_path, 0777);
}

std::string Mere::XDG::IconSoftLinkCache::get(const std::string &key, bool *flag)
{
    if (m_cache)
    {
        bool _flag;
        std::string path = m_cache->get(key, &_flag);
        if (_flag)
        {
            if (flag) *flag = true;
            return path;
        }
    }

    std::string path(m_path);
    path.append(key);
    if(!Mere::Utils::FileUtils::isExist(path))
    {
        if (flag) *flag = false;
        return "";
    }

    char link[4096]; /* maxsize of path - 4096 ? */
    int bytes = readlink(path.c_str(), link, sizeof(link));
    if (!bytes)
    {
        if (flag) *flag = false;
        return "";
    }
    link[bytes] = '\0';

    std::string value(link);

    if (m_cache) m_cache->set(key, value);

    return value;
}

void Mere::XDG::IconSoftLinkCache::set(const std::string &key, const std::string &link)
{
    if (key.empty()) return;

    auto pos = key.find("/");
    if (pos != std::string::npos) return;

    if (link.empty())
    {
        std::string path(m_path);
        path.append(key);

        Mere::Utils::FileUtils::remove(path);

        return;
    }

    // set it
    if(m_cache) m_cache->set(key, link);

    std::string path(m_path);
    symlink(link.c_str(), path.append(key).c_str());
}

void Mere::XDG::IconSoftLinkCache::setCache(IconMemoryCache *cache)
{
    m_cache = cache;
}
