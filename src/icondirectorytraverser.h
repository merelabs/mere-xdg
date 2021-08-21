#ifndef ICONDIRECTORYTRAVERSER_H
#define ICONDIRECTORYTRAVERSER_H

#include "global.h"
#include <QObject>

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC IconDirectoryTraverser : public QObject
{
    Q_OBJECT
public:
    explicit IconDirectoryTraverser(QObject *parent = nullptr);
    std::vector<std::string> traverse(const std::string &path, const std::string &name) const;

private:
    std::vector<std::string> files(const std::string &path, const std::string &name) const;

signals:

};

}
}

#endif // ICONDIRECTORYTRAVERSER_H
