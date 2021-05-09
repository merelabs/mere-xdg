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
    auto it = std::find(m_keys.begin(), m_keys.end(), key);
    if (it == m_keys.end())
    {
        if (flag) *flag = false;
        return "";
    }

    // check if it already in front
    if (it != m_keys.begin())
        m_keys.splice(m_keys.begin(), m_keys, it);

    if (flag) *flag = true;
    return m_cache.at(m_keys.begin());
}

void Mere::XDG::IconMemoryCache::set(const std::string &key, const std::string &value, bool *flag)
{
    auto it = std::find(m_keys.begin(), m_keys.end(), key);
    if (it == m_keys.end())
    {
        if (flag) *flag = false;

        m_keys.push_front(key);
        if (m_keys.size() > m_capacity)
        {
            m_cache.erase(std::prev(m_keys.end()));
            m_keys.pop_back();
        }
    }
    else
    {
        if (flag) *flag = true;
        if (it != m_keys.begin())
            m_keys.splice(m_keys.begin(), m_keys, it);
    }

    m_cache[m_keys.begin()] = value;
}

void Mere::XDG::IconMemoryCache::print()
{
    for (auto& key : m_keys)
        std::cout << key << std::endl;

    for (auto& cache : m_cache)
        std::cout << *cache.first << "\t => " << cache.second << std::endl;
}
