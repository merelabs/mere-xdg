#include "iconlinkcache.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>

#include <QDebug>

unsigned int Mere::XDG::IconLinkCache::g_mage     = 0;
unsigned int Mere::XDG::IconLinkCache::g_dage     = 0;
unsigned int Mere::XDG::IconLinkCache::g_capacity = 0;
std::string  Mere::XDG::IconLinkCache::g_path     = "~/.cache";
std::map<std::string, unsigned int> Mere::XDG::IconLinkCache::g_age = {};
std::map<std::string, std::string> Mere::XDG::IconLinkCache::g_cache = {};


Mere::XDG::IconLinkCache::IconLinkCache(QObject *parent)
    : QObject(parent)
{

}

void Mere::XDG::IconLinkCache::setCache(const std::string &path)
{
    g_path = path;
    if (g_path.empty()) return;

    if(g_path.back() != '/')
        g_path.append("/");
}

void Mere::XDG::IconLinkCache::setAge(unsigned int age, const Type &type)
{
    switch (type)
    {
        case Type::Disk:
            g_dage = age;
            break;

        case Type::Memory:
            g_mage = age;
            break;
    }
}

void Mere::XDG::IconLinkCache::setCapacity(unsigned int capacity)
{
    g_capacity = capacity;
}

std::string Mere::XDG::IconLinkCache::get(const std::string &key)
{
    auto find = g_cache.find(key);
    if (find != g_cache.end())
        return find->second;

    std::string path(g_path);
    std::fstream file(path.append(key));
    if (file.good())
    {
        char link[4096]; /* maxsize of path - 4096 ? */
        int bytes = readlink(path.c_str(), link, sizeof(link));

        if (bytes)
        {
            std::string value(link);
            g_cache.insert({key, value});

            return value;
        }
    }

    return "";
}

void Mere::XDG::IconLinkCache::set(const std::string &key, const std::string &link)
{
    if (key.empty()) return;

    auto pos = key.find("/");
    if (pos != std::string::npos) return;

    if (link.empty())
    {
        g_cache.erase(key);

        std::string path(g_path);

        std::fstream file(path.append(key));
        if (file.good())
        {
            std::remove(path.c_str());
        }

        return;
    }

    // set it
    g_cache.insert({key, link});

    std::string path(g_path);
    symlink(link.c_str(), path.append(key).c_str());
    qDebug() << link.c_str() << path.c_str();
}
