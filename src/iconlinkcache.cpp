#include "iconlinkcache.h"
#include "mere/utils/pathutils.h"
#include "mere/utils/fileutils.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>

Mere::XDG::IconLinkCache::~IconLinkCache()
{
}

Mere::XDG::IconLinkCache::IconLinkCache()
    : IconLinkCache("/tmp/mere/xdg/icon/")
{
}

Mere::XDG::IconLinkCache::IconLinkCache(const std::string &path)
{
    setPath(path);
}

void Mere::XDG::IconLinkCache::setPath(const std::string &path)
{
    if (path.empty()) return;

    m_path = path;

    if(m_path.back() != '/')
        m_path.append("/");

    Mere::Utils::PathUtils::create_if_none(m_path);
}

void Mere::XDG::IconLinkCache::setAge(unsigned int age, const Type &type)
{
    switch (type)
    {
        case Type::Disk:
            m_dage = age;
            break;

        case Type::Memory:
            m_mage = age;
            break;
    }
}

void Mere::XDG::IconLinkCache::setCapacity(unsigned int capacity)
{
    m_capacity = capacity;
}

std::string Mere::XDG::IconLinkCache::get(const std::string &key)
{
    auto find = m_cache.find(key);
    if (find != m_cache.end())
        return find->second;

    std::string path(m_path);
    path.append(key);
    if(!Mere::Utils::FileUtils::isExist(path))
        return "";

    char link[4096]; /* maxsize of path - 4096 ? */
    int bytes = readlink(path.c_str(), link, sizeof(link));
    if (!bytes) return "";

    std::string value(link);
    m_cache.insert({key, value});

    return value;
}

void Mere::XDG::IconLinkCache::set(const std::string &key, const std::string &link)
{
    qDebug() << "1...." << key.c_str() << link.c_str();
    if (key.empty()) return;

    auto pos = key.find("/");
    if (pos != std::string::npos) return;

    if (link.empty())
    {
        m_cache.erase(key);

        std::string path(m_path);

        std::fstream file(path.append(key));
        if (file.good())
        {
            std::remove(path.c_str());
        }

        return;
    }

    // set it
    m_cache.insert({key, link});

    std::string path(m_path);
    symlink(link.c_str(), path.append(key).c_str());
}
