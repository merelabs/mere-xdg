#ifndef MERE_XDG_ICONTHEME_H
#define MERE_XDG_ICONTHEME_H

#include "global.h"

#include <QObject>
namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC IconTheme : public QObject
{
    Q_OBJECT
public:
    explicit IconTheme(const QString &themePath, QObject *parent = nullptr);
};
}
}

#endif // MERE_XDG_ICONTHEME_H
