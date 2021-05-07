#include "iconmemorycache.h"
#include <iostream>
#include <algorithm>
Mere::XDG::IconMemoryCache::IconMemoryCache(unsigned int capacity)
    : m_capacity(capacity)
{

}

bool Mere::XDG::IconMemoryCache::has(const std::string &key) const
{
    return std::find(m_keys.cbegin(), m_keys.cend(), key) != m_keys.cend();
}

std::string Mere::XDG::IconMemoryCache::get(const std::string &key, bool *flag)
{
    auto it = std::find(m_keys.cbegin(), m_keys.cend(), key);
    if (it == m_keys.cend())
    {
        if (flag) *flag = false;
        return "";
    }

    // check if it already in front
    if (it != m_keys.cbegin())
    {
        //m_keys.erase(it);
        //m_keys.push_front(key);
        m_keys.splice(m_keys.begin(), m_keys, it);
    }

    if (flag) *flag = true;
    return m_cache.at(key);
}

void Mere::XDG::IconMemoryCache::set(const std::string &key, const std::string &value, bool *flag)
{
    m_cache[key] = value;

    auto it = std::find(m_keys.cbegin(), m_keys.cend(), key);
    if (it == m_keys.cend())
    {
        if (flag) *flag = false;

        m_keys.push_front(key);
        if (m_keys.size() > m_capacity)
        {
            m_cache.erase(m_keys.back());
            m_keys.pop_back();
        }
    }
    else
    {
        if (flag) *flag = true;

        if (it != m_keys.cbegin())
        {
            //m_keys.erase(it);
            //m_keys.push_front(key);
            m_keys.splice(m_keys.begin(), m_keys, it);
        }
    }
}

void Mere::XDG::IconMemoryCache::print()
{
    for (auto& cache : m_cache)
        std::cout << cache.first << "\t => " << cache.second << std::endl;
}
