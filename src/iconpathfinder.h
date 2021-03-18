#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "global.h"

#include "iconlinkcache.h"
#include <QObject>

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC IconPathFinder : public QObject
{
    Q_OBJECT
public:
    explicit IconPathFinder(QObject *parent = nullptr);
    void setCache(IconLinkCache *cache);

    std::string find(const std::string &icon);

signals:

private:
    IconLinkCache *m_cache;
};

}
}

#endif // PATHFINDER_H
