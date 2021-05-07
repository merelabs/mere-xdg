#ifndef ICONMEMORYCACHE_H
#define ICONMEMORYCACHE_H

#include <list>
#include <string>
#include <unordered_map>

namespace Mere
{
namespace XDG
{

class IconMemoryCache
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
    std::unordered_map<std::string, std::string> m_cache;
};

}
}

#endif // ICONMEMORYCACHE_H
