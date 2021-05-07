#ifndef MERE_XDG_ICONDISKCACHE_H
#define MERE_XDG_ICONDISKCACHE_H

#include "global.h"

#include <map>

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC IconLinkCache
{
public:
    ~IconLinkCache();
    IconLinkCache();
    explicit IconLinkCache(const std::string &path);

    enum class Type
    {
        Disk,
        Memory
    };

    void setAge(unsigned int age, const Type &type);
    void setCapacity(unsigned int capacity);

    void setPath(const std::string &path);

    std::string get(const std::string &key);
    void set(const std::string &key, const std::string &link);

private:
    std::string m_path;

    unsigned int m_mage;
    unsigned int m_dage;
    unsigned int m_capacity;

    std::map<std::string, unsigned int> m_age;
    std::map<std::string, std::string> m_cache;
};

}
}

#endif // MERE_XDG_ICONDISKCACHE_H
