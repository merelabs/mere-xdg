#ifndef MERE_XDG_ICONPATHFINDER_H
#define MERE_XDG_ICONPATHFINDER_H

#include "global.h"
#include <QObject>

namespace Mere
{
namespace XDG
{
class IconSoftLinkCache;

class MERE_XDG_LIB_SPEC IconPathFinder : public QObject
{
    Q_OBJECT
public:
    ~IconPathFinder();
    explicit IconPathFinder(QObject *parent = nullptr);
    void setCache(IconSoftLinkCache *cache);

    std::string find(const std::string &icon);

private:
    IconSoftLinkCache *m_cache;
};

}
}

#endif // MERE_XDG_ICONPATHFINDER_H
