#ifndef MERE_XDG_ICONDISKCACHE_H
#define MERE_XDG_ICONDISKCACHE_H

#include "global.h"

#include <map>

namespace Mere
{
namespace XDG
{

class IconMemoryCache;

class MERE_XDG_LIB_SPEC IconSoftLinkCache
{
public:
    ~IconSoftLinkCache();
    IconSoftLinkCache();
    explicit IconSoftLinkCache(const std::string &path);

    void setPath(const std::string &path);

    std::string get(const std::string &key);
    void set(const std::string &key, const std::string &link);

    void setCache(IconMemoryCache *cache);

private:
    std::string m_path;
    IconMemoryCache *m_cache;
};

}
}

#endif // MERE_XDG_ICONDISKCACHE_H
