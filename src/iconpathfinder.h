#ifndef MERE_XDG_ICONPATHFINDER_H
#define MERE_XDG_ICONPATHFINDER_H


#include "global.h"

namespace Mere::XDG
{
class IconSoftLinkCache;

class MERE_XDG_LIB_SPEC IconPathFinder
{
public:
    ~IconPathFinder() = default;
    IconPathFinder() = default;

    void setCache(IconSoftLinkCache *cache);

    std::string find(const std::string &icon);

private:
    IconSoftLinkCache *m_cache;
};

}


#endif // MERE_XDG_ICONPATHFINDER_H
