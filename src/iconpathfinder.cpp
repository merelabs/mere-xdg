#include "iconpathfinder.h"
#include "mere/xdg/iconlookuphelper.h"

Mere::XDG::IconPathFinder::IconPathFinder(QObject *parent) : QObject(parent)
{

}

void Mere::XDG::IconPathFinder::setCache(IconLinkCache *cache)
{
    m_cache = cache;
}

std::string Mere::XDG::IconPathFinder::find(const std::string &icon)
{
    std::string path;

    if (m_cache)
    {
        path = m_cache->get(icon);
        if (!path.empty()) return path;
    }

    path = IconLookupHelper::path(icon);
    if(path.empty())
    {
        // FIXME: if no icon found????
        path = IconLookupHelper::path("applications-development");
    }

    if (m_cache && !path.empty())
        m_cache->set(icon, path);

    return path;
}

