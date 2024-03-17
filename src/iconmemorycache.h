#ifndef ICONMEMORYCACHE_H
#define ICONMEMORYCACHE_H

#include "global.h"

#include <list>
#include <string>
#include <unordered_map>

namespace Mere::XDG
{

typedef std::list<std::string>::iterator KeyIterator;
struct KeyHash
{
    size_t operator()(const std::list<std::string>::iterator &that) const
    {
        return std::hash<std::string>()(*that);
    }
};

class MERE_XDG_LIB_SPEC IconMemoryCache
{
public:
    explicit IconMemoryCache(unsigned int capacity);

    bool has(const std::string &key) const;
    std::string get(const std::string &key, bool *flag = nullptr);
    void set(const std::string &key, const std::string &value, bool *flag = nullptr);

    void print();

private:
    unsigned int m_capacity;
    unsigned int m_age;

    std::list<std::string> m_keys;
    std::unordered_map<KeyIterator, std::string, KeyHash> m_cache;
};

}

#endif // ICONMEMORYCACHE_H
